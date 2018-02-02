#include "html.hh"
using el = OB::Html::Element;
using css = OB::Html::Css;

#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  // create the head element
  el head("head"); head
  (el("title").sin("example"))
  (el("meta", {{"charset", "utf-8"}}))
  (el("meta", {{"name", "description"}, {"content", "example doc"}}))
  ;

  // create the body
  el body("body");

  // create the standard html structure
  // add the head and body as children
  el html("html", {{"lang", "en"}}); html
  (head)
  (body)
  ;

  // create the content
  // a div with an h1 containing 'Hello, World!'
  el content("div", "content"); content
  (el("h1").sin("Hello, World!"))
  ;

  // add the content to the document
  html[1](content);

  // render the html to a string
  std::string output {html.str()};

  // output the result
  std::cout << output << "\n";

  return 0;
}
