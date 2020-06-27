import tornado
from tornado.web import RequestHandler, Application


class MainHandler(RequestHandler):
    def get(self):
        self.render("index.html")


class Year2000Handler(RequestHandler):
    def get(self):
        self.render("output_2000.html")


class Year2016Handler(RequestHandler):
    def get(self):
        self.render("output_2016.html")


def make_app():
    return Application([
        (r"/", MainHandler),
        (r"/2016/", Year2016Handler),
        (r"/2000/", Year2000Handler),
    ])


if __name__ == "__main__":
    app = make_app()
    app.listen(8080)
    print("Running on http://localhost:8080")
    tornado.ioloop.IOLoop.current().start()
