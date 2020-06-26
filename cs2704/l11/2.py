from tornado.web import RequestHandler, Application

class MainHandler(RequestHandler):
  def get(self):
    self.render("index2.html")
    
class TableHandler(RequestHandler):
  def post(self):
    midterm = float(self.get_body_argument("midterm"))
    final = float(self.get_body_argument("final"))
    self.render("sum.html", data=(midterm,final,midterm+final))

def make_app():
  return Application([
    (r"/", MainHandler),
    (r"/sum", TableHandler)
  ])

if __name__ == "__main__":
  app = make_app()
  app.listen(8080)
