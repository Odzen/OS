from sqlite3 import Cursor
from sqlalchemy import PrimaryKeyConstraint
from flask import Flask
import sqlalchemy as sqla
from flask_sqlalchemy import SQLAlchemy
from pprint import pprint

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




def get_hit_count():
    retries = 5
    print("Entro normal")
    me = User('admin')
    db.session.add(me)
    db.session.commit()
    list=User.query.limit(1).all()
    value=list[0]
    typeValue=print(type(value))
    #User.query.filter_by(id=value).delete()
    db.session.delete(me)
    db.session.commit()
    #print(value)
    return value


@app.route('/')

def index():
    # Create a user.
    hits=get_hit_count()
    print("Entro normal")
    return 'hello {} times flask\n</h1>'.format(hits)


User.__table__.drop(sqla.create_engine("postgresql://postgres:postgres2819@localhost/flaskmovie", echo=True))

db.create_all()

if __name__=="__main__":
    app.run()