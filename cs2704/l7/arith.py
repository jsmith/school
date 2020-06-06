import random

class Game:
  def __init__(self):
    self.x = 3
    self.y = 4
    self.op = 1

  def op_str(self):
    if self.op == 1:
      return "+"
    elif self.op == 2:
      return "-"
    elif self.op == 3:
      return "*"
    else:
      return None
 
  def new_game(self):
    self.x = random.randint(1,9)
    self.y = random.randint(1,9)
    self.op = random.randint(1,3)
 
  def answer(self):
    if self.op == 1:
      return self.x + self.y
    elif self.op == 2:
      return self.x - self.y
    elif self.op == 3:
      return self.x * self.y
    else:
      return None

game = Game()

from tornado.web import RequestHandler,Application

class Home(RequestHandler):
  def get(self):
    self.render("prompt.html",
      x = game.x,
      y = game.y,
      op=game.op_str())

class Answer(RequestHandler):
  def post(self):
    answer = self.get_body_argument("answer")
    if int(answer) == game.answer():
      self.render("correct.html",a=answer)
    else:
      self.render("wrong.html",
        x=game.x,
        y=game.y,
        op=game.op_str(),
        a=answer,
        b=game.answer())

class NewGame(RequestHandler):
 def get(self):
    game.new_game()
    self.render("prompt.html",
    x = game.x,
    y = game.y,
    op=game.op_str())

def make_app():
  home = ("/test/",Home)
  answer = ("/test/answer",Answer)
  new_game = ("/test/new", NewGame)
  all_paths = [home,answer,new_game]

  return Application(all_paths)

app = make_app()
server = app.listen(8080)
