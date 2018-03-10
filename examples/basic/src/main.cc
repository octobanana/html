#include "html.hh"
using el = OB::Html::Element;
using css = OB::Html::Css;

#include <string>
#include <iostream>

std::string render_css();

std::string render_css()
{
  // css object
  css style;

  // add html selector
  style.add("html", {
    {"height", "100%"},
    {"font-weight", "normal"},
    {"font-size", "16px"},
  });

  // add content id selector
  style.add("#content", {
    {"border", "1px solid #000000"},
    {"border-radius", "5px"},
  });

  // add centered text class selector
  style.add(".center", {
    {"text-align", "center"},
  });

  // render the css to a string
  return style.str();
}

int main(int argc, char *argv[])
{
  // create the head element
  el head("head"); head
  (el("title").sin("example"))
  (el("meta", {{"charset", "utf-8"}}))
  (el("meta", {{"name", "description"}, {"content", "example doc"}}))
  ;

  // append style element to head
  // el::sin("") sets the inner text of the element
  head(el("style", "style").sin(render_css()));

  // create the body
  el body("body");

  // create the standard html structure
  // add the head and body as children
  // adding a child is done with el::operator()
  el html("html", {{"lang", "en"}}); html
  (head)
  (body)
  ;

  // create the content
  // a div with an h1 containing 'Hello, World!'
  el content("div", "content"); content
  (el("h1", {{"class", "center"}}).sin("Hello, World!"))
  ;

  // add the content to the document
  // access child elements through array int or by id string
  html[1](content);

  // render the html to a string
  std::string output {html.str()};

  // output the result with doctype
  std::cout << "<!DOCTYPE html>" << output << "\n";

  return 0;
}
