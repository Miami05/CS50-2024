import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    transactions = db.execute('''
                             SELECT symbol, SUM(shares) AS shares, MAX(price) AS price, SUM(shares * price) as total_value FROM transactions WHERE user_id = ?
                             GROUP BY symbol HAVING SUM(shares) > 0''', user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    total_stock_value = 0
    stocks_data = []
    for transaction in transactions:
        symbol = transaction["symbol"]
        shares = transaction["shares"]
        price = transaction["price"]
        total_value = shares * price
        total_stock_value += total_value

        stocks_data.append({
            "symbol": symbol,
            "shares": shares,
            "price": price,
            "total_value": total_value
        })
    status = total_stock_value + cash

    return render_template("index.html", stocks_data=stocks_data, status=status, cash=cash)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change user passsword"""
    if request.method == "POST":
        password = request.form.get("password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirmation")

        # Check if the password is correct
        user_id = session["user_id"]
        user = db.execute("SELECT hash FROM users WHERE id = ?", user_id)
        print(user)

        # Ensure that user is a list of dictionaries
        if not user or not check_password_hash(user[0]["hash"], password):
            flash("Current password is incorrect!")
            return redirect("/password")

        # Check if the password is valid
        if not new_password or not confirm_password or new_password != confirm_password:
            flash("New passwords does not match or are invalid")
            return redirect("/password")

        # Update it into database
        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   generate_password_hash(new_password), user_id)
        flash("Password Changed")
        return redirect("/")

    return render_template("password.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if the symbol is valid
        if not symbol:
            return apology("MISSING SYMBOL", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("INVALID SYMBOL")

        # Check if shares is a positive integer
        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("Value must be greater than or equal to 1")

        # Get user's cash balance
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # Calculate cost of the shares
        cost = stock["price"] * int(shares)

        # Check if user can afford the shares
        if cost > cash:
            return apology("CANT'T AFFORD", 400)

        # Calculate remaining cash after purchase
        new_cash = cash - cost

        # Check if user already has shares of this stock
        existing_stock = db.execute(
            "SELECT shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)

        if existing_stock:
            db.execute('''
                       UPDATE transactions SET shares = shares + ?, total_value = ?
                       WHERE symbol = ? AND user_id = ?''', int(shares), stock["price"] * int(shares), symbol, user_id)
        else:
            # Insert transaction into transactions table
            db.execute('''
                       INSERT INTO transactions (user_id, symbol, price, shares, total_value)
                        VALUES (?, ?, ?, ?, ?)
                        ''', user_id, symbol, stock["price"], int(shares), stock["price"] * int(shares))
        # Update user's cash balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
        flash("Bought!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions")
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Check if the symbol is valid
        if not symbol:
            return apology("MISSING SYMBOL", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("INVALID SYMBOL")

        return render_template("quoted.html", stock=stock)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password_confirm = request.form.get("confirmation")

        # Check if username password and password_confirm are empty
        if not username:
            return apology("must provide username", 400)

        if not password:
            return apology("must provide password", 400)

        if not password_confirm:
            return apology("must provide confirm password", 400)

        # Check if password doesn't match with each other
        if password != password_confirm:
            return apology("Passwords doesn't match", 400)

        # Check get the users from the database and check if it's taken or no
        taken = db.execute("SELECT username FROM users WHERE username = ?", (username,))
        if taken:
            return apology("This username has already been taken. Please pick another username", 400)

        # If it's not taken is inserting into the database
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)",
                   username, generate_password_hash(password))

        return redirect("/")
    return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("missing symbol", 400)
        if not shares:
            return apology("Missing shares", 400)
        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("share must be positive number", 1)
        stock = db.execute("SELECT SUM(shares) AS shares, MAX(price) AS price FROM transactions WHERE symbol = ? AND user_id = ?",
                           symbol, session["user_id"])
        if not stock or stock[0]["shares"] is None:
            return apology("No share to sell at this stock", 400)
        user_shares = stock[0]['shares']
        share_to_sell = int(shares)
        if share_to_sell > user_shares:
            return apology("too many shares", 400)
        price_per_share = stock[0]['price']
        value_per_share = price_per_share * share_to_sell

        if user_shares == int(shares):
            db.execute("DELETE FROM transactions WHERE symbol = ? AND user_id = ?",
                       symbol, session["user_id"])
        else:
            db.execute('''
                       UPDATE transactions SET shares = shares - ?, total_value = (shares - ?) * price WHERE symbol = ? AND user_id = ?
                       ''', share_to_sell,  share_to_sell, symbol, session["user_id"])

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   value_per_share, session["user_id"])
        flash("Sold!")
        return redirect("/")

    symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("sell.html", symbols=symbols)
