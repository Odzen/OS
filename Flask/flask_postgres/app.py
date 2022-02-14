import psycopg2
from psycopg2 import Error
import time
from sqlalchemy import PrimaryKeyConstraint
from flask import Flask
import sqlalchemy as sqla
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
    id=db.Column(db.Integer, primary_key=True,autoincrement=True)
    username=db.Column(db.String(80),unique=True)

    def __init__(self,username):
        self.username=username
    
    def __repr__(self):
        return '{}'.format(self.id)

#Funcion que me devuelve un contador
def get_hit_count():
    retries = 5
    try:
        me = User('admin')
        db.session.add(me)
        db.session.commit()
        list=User.query.limit(1).all()
        value=list[0]
        db.session.delete(me)
        db.session.commit()
        return value
    except (Exception, Error) as error:
        if retries == 0:
            print("Error while connecting to PostgreSQL", error)
            raise error
        retries -= 1
        time.sleep(0.5)


@app.route('/')

def index():
    hits=get_hit_count()
    return 'hello {} times flask\n'.format(hits)

#Elimino tabla
User.__table__.drop(sqla.create_engine("postgresql://postgres:postgres2819@localhost/flaskmovie", echo=True))
#Vuelvo a crear la tabla a partir del esquema
db.create_all()