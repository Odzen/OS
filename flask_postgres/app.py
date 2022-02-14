from sqlalchemy import PrimaryKeyConstraint
from flask import Flask
from flask_sqlalchemy import SQLAlchemy


##Creando APP
app=Flask(__name__)

#Configurando config
#SQLALCHEMY_DATABASE_URI -> key value
#Each database has a different config string
#En el caso de postgres es: postgresql://postgres:password@localhost/flaskmovie
app.config['SQLALCHEMY_DATABASE_URI']='postgresql://postgres:postgres2819@localhost/flaskmovie'


##Creado db objects y pasar la app
db=SQLAlchemy(app)

##Crear tablas y esquema de la base de datos

class User(db.Model):
    id=db.Column(db.Integer, primary_key=True)
    username=db.Column(db.String(80),unique=True)
    email=db.Column(db.String(120), unique=True)

    def __init__(slef,username,email):
        self.username=username
        self.email=email
    
    def __repr__(self):
        return '<User %r>' % self.username


@app.route('/')

def index():
    return "<h1 style='color:red'> hello flask</h1>"

if __name__=="__main__":
    app.run()