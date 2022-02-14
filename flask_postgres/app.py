from flask import Flask
from flask_sqlalchemy import SQLAlchemy


##Creando APP
app=Flask(__name__)

#Configurando config
#SQLALCHEMY_DATABASE_URI -> key value
#Each database has a different config string
#En el caso de postgres es: postgresql://postgres:password@localhost/flaskmovie
app.config['SQLALCHEMY_DATABASE_URI']='postgresql://postgres:password@localhost/flaskmovie'

##Crear tablas y esquema de la base de datos
##Creado db objects y pasar la app
db=SQLAlchemy(app)

@app.route('/')

def index():
    return "<h1 style='color:red'> hello flask</h1>"

if __name__=="__main__":
    app.run()