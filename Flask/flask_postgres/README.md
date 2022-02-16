# App with Flask and PostgreSQL in localhost
Python mini excercise, that will create all an app in flask that will use postgres to storage a value, and then print it to the server. The value will increment for each call to the server. 
## To execute:
- export FLASK_APP=app.py
- flask run

Keep in mind that the app.config changes depending on the user and password that is installed for postgres on each machine. To execute change the line #16 to 'postgresql://user:password@localhost/database_name'
