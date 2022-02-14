from app import User

me = User('admin', 'admin@example.com')
db.session.add(me)
db.session.commit()