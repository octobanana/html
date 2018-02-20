//
// MIT License
//
// Copyright (c) 2018 Brett Robinson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef OB_HTML_HH
#define OB_HTML_HH

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace OB
{
namespace Html
{

enum class Tag
{
  comment, // !-- --
  doctype, // !DOCTYPE
  a,
  abbr,
  address,
  area,
  article,
  aside,
  audio,
  b,
  base,
  bdi,
  bdo,
  blockquote,
  body,
  br,
  button,
  canvas,
  caption,
  cite,
  code,
  col,
  colgroup,
  data,
  datalist,
  dd,
  del,
  details,
  dfn,
  dialog,
  div,
  dl,
  dt,
  em,
  embed,
  fieldset,
  figcaption,
  figure,
  footer,
  form,
  h1,
  head,
  header,
  hr,
  html,
  i,
  iframe,
  img,
  input,
  ins,
  kbd,
  keygen,
  label,
  legend,
  li,
  link,
  main,
  map,
  mark,
  menu,
  menuitem,
  meta,
  meter,
  nav,
  noscript,
  object,
  ol,
  optgroup,
  option,
  output,
  p,
  param,
  picture,
  pre,
  progress,
  q,
  rp,
  rt,
  ruby,
  s,
  samp,
  script,
  section,
  select,
  small,
  source,
  span,
  strong,
  style,
  sub,
  summary,
  sup,
  table,
  tbody,
  td,
  textarea,
  tfoot,
  th,
  thead,
  time,
  title,
  tr,
  track,
  u,
  ul,
  var,
  video,
  wbr
};

class Element
{
public:

  using attr = std::map<std::string, std::string>;

  Element(std::string _tag, attr _attributes):
    tag_ {_tag},
    id_ {},
    attributes_ {_attributes},
    class_ {},
    inner_html_ {},
    children_ {},
    is_child_ {false},
    is_inline_ {false},
    is_tag_void_ {false},
    level_ {0},
    indent_spaces_ {0}
  {
    init();
  }

  Element(std::string _tag = "div", std::string _id = {}, attr _attributes = {}):
    tag_ {_tag},
    id_ {_id},
    attributes_ {_attributes},
    class_ {},
    inner_html_ {},
    children_ {},
    is_child_ {false},
    is_inline_ {false},
    is_tag_void_ {false},
    level_ {0},
    indent_spaces_ {0}
  {
    init();
  }

  Element& add_child(Element _elem)
  {
    _elem.is_child();
    children_.emplace_back(_elem);
    return *this;
  }

  std::vector<Element>& get_children()
  {
    return children_;
  }

  Element& last_child()
  {
    return children_.at(children_.size() - 1);
  }

  std::string gid()
  {
    return id_;
  }

  Element& sid(std::string const _id)
  {
    id_ = _id;
    return *this;
  }

  std::string gn()
  {
    return name_;
  }

  Element& sn(std::string const _name)
  {
    name_ = _name;
    return *this;
  }

  Element& last_inner_child()
  {
    Element& elem = *this;
    if (! children_.empty())
    {
      elem = last_child().last_inner_child();
    }
    return elem;
  }

  Element& tag(std::string _tag)
  {
    tag_ = _tag;
    return *this;
  }

  std::string gattr(std::string key)
  {
    if (key == "id")
    {
      return id_;
    }

    std::string out;
    if (attributes_.find(key) != attributes_.end())
    {
      out = attributes_.at(key);
    }
    return out;
  }

  Element& sattr(std::string key, std::string value)
  {
    if (key == "id")
    {
      id_ = value;
    }
    attributes_[key] = value;
    return *this;
  }

  std::string gat(std::string const key)
  {
    std::string out;
    if (attributes_.find(key) != attributes_.end())
    {
      out = attributes_.at(key);
    }
    return out;
  }

  Element& sat(attr const _attr)
  {
    for (auto const& e : _attr)
    {
      attributes_[e.first] = e.second;
    }
    return *this;
  }

  Element& aat(attr const _attr)
  {
    for (auto const& e : _attr)
    {
      attributes_[e.first] += " " + e.second;
    }
    return *this;
  }

  Element& inner_html(std::string _inner_html)
  {
    inner_html_ = _inner_html;
    return *this;
  }

  std::string gin()
  {
    return inner_html_;
  }

  Element& sine(std::string _inner_html)
  {
    // escape special chars
    _inner_html = str_replace(_inner_html, "&", "&amp");
    _inner_html = str_replace(_inner_html, "<", "&lt");
    _inner_html = str_replace(_inner_html, ">", "&gt");
    _inner_html = str_replace(_inner_html, "\"", "&quot");
    _inner_html = str_replace(_inner_html, "'", "&#39");
    inner_html_ = _inner_html;
    return *this;
  }

  Element& sin(std::string _inner_html)
  {
    inner_html_ = _inner_html;
    return *this;
  }

  Element& ain(std::string _inner_html)
  {
    inner_html_ += _inner_html;
    return *this;
  }

  Element& aine(std::string _inner_html)
  {
    // escape special chars
    _inner_html = str_replace(_inner_html, "&", "&amp");
    _inner_html = str_replace(_inner_html, "<", "&lt");
    _inner_html = str_replace(_inner_html, ">", "&gt");
    _inner_html = str_replace(_inner_html, "\"", "&quot");
    _inner_html = str_replace(_inner_html, "'", "&#39");
    inner_html_ += _inner_html;
    return *this;
  }

  Element& add_class(std::string _class)
  {
    if (class_.empty())
    {
      class_.append(_class);
    }
    else
    {
      class_.append(" " + _class);
    }
    return *this;
  }

  Element& at(std::string _id)
  {
    for (auto &c : children_)
    {
      if (c.id_ == _id)
      {
        return c;
      }
      else
      {
        c.at(_id);
      }
    }
    return *this;
  }

  std::string str()
  {
    // std indent
    std::string in;
    // for (int i = 0; i < indent_spaces_; ++i)
    // {
    //   in.append(" ");
    // }

    // child indent
    std::string in_ch;
    // int calc_indent {indent_spaces_ * level_};
    // for (int i = 0; i < calc_indent; ++i)
    // {
    //   in_ch.append(" ");
    // }

    // space
    std::string sp {" "};

    // new line alias
    std::string nl {""};

    // renderend Element(s) container
    std::string el;
    el.reserve(1024);

    // tag open
    // if (is_child_ && (! is_inline_))
    // {
    //   el.append(nl + in_ch);
    // }
    el.append("<" + tag_);

    // id
    if (! id_.empty())
    {
      el.append(sp + "id=\"" + id_ + "\"");
    }

    // class
    if (! class_.empty())
    {
      el.append(sp + "class=\"" + class_ + "\"");
    }

    // other attributes
    for (const auto &a : attributes_)
    {
      el.append(sp + a.first);
      if (! a.second.empty())
      {
        el.append("=\"" + a.second + "\"");
      }
    }
    el.append(">");

    // check if void tag
    if (is_tag_void_)
    {
      return el;
    }

    // inner html
    if (! inner_html_.empty())
    {
      el.append(nl + in);

      // if (is_child_ && (! is_inline_))
      // {
      //   el.append(in_ch);
      // }
      el.append(inner_html_);
    }

    // child Element(s)
    if (! children_.empty())
    {
      for (auto &e : children_)
      {
        el.append(e.str());
      }
    }

    // tag close
    el.append(nl);
    // if (is_child_ && (! is_inline_))
    // {
    //   el.append(in_ch);
    // }
    el.append("</" + tag_ + ">");

    return el;
  }

  // array access to child Elements by id
  Element& operator[](std::string _id)
  {
    for (auto &c : children_)
    {
      if (c.id_ == _id)
      {
        return c;
      }
    }
    return *this;
  }

  // array access to child Elements by order
  Element& operator[](int _child)
  {
    auto& children = get_children();
    return children.at(_child);
  }

  // add child Element
  Element& operator()(Element _elem)
  {
    _elem.is_child();
    children_.emplace_back(_elem);
    return *this;
  }

  Element& operator<(Element _el)
  {
    add_child(std::move(_el));
    return *this;
  }

  Element& operator<<(Element _el)
  {
    last_inner_child().add_child(std::move(_el));
    return last_inner_child();
  }

  Element operator=(Element _el)
  {
    return *this;
  }

  // set Element as inlne
  // TODO account for inline Elements in render
  Element& il(bool _inline)
  {
    is_inline_ = _inline;
  }

private:
  std::string name_;
  std::string tag_;
  std::string id_;
  std::map<std::string, std::string> attributes_;
  std::string class_;
  std::string inner_html_;
  std::vector<Element> children_;
  bool is_child_;
  bool is_inline_;
  bool is_tag_void_;
  int level_;

  // for pretty printing
  int indent_spaces_;

  void init()
  {
    is_tag_void();
  }

  void is_inline()
  {
    is_inline_ = true;
  }

  void is_tag_void()
  {
    if (tag_ == "area" ||
      tag_ == "base" ||
      tag_ == "br" ||
      tag_ == "col" ||
      tag_ == "command" ||
      tag_ == "embed" ||
      tag_ == "hr" ||
      tag_ == "img" ||
      tag_ == "input" ||
      tag_ == "keygen" ||
      tag_ == "link" ||
      tag_ == "meta" ||
      tag_ == "param" ||
      tag_ == "source" ||
      tag_ == "track" ||
      tag_ == "wbr")
    {
      is_tag_void_ = true;
    }
  }

  void is_child()
  {
    ++level_;
    if (! children_.empty())
    {
      for (auto &e : children_)
      {
        e.is_child();
      }
    }
    is_child_ = true;
  }

  std::string str_replace(std::string str, std::string key, std::string val)
  {
    std::string::size_type pos_start = 0;
    size_t len_key {key.length()};

    do
    {
      pos_start = str.find(key, ++pos_start);
      if (pos_start != std::string::npos)
      {
        str.replace(pos_start, len_key, val);
      }
    }
    while (pos_start != std::string::npos);
    return str;
  }
}; // class Element

class Css
{
public:
  class Media
  {
  public:
    Media()
    {
    }

    Media& add(std::string k, Css v)
    {
      _media.emplace(std::make_pair(k, v));
      _has_changed = true;
      return *this;
    }

    std::string str()
    {
      if (_has_changed)
      {
        for (auto &e : _media)
        {
          _str += "@media(" + e.first + "){";
          _str += e.second.str();
          _str += "}";
        }
        _has_changed = false;
      }
      return _str;
    }

  private:
    bool _has_changed {false};
    std::string _str;
    std::multimap<std::string, Css> _media;
  }; // class Media

  Css()
  {
  }

  Css& add(std::string k, std::multimap<std::string, std::string> v)
  {
    _css[k] = v;
    _has_changed = true;
    return *this;
  }

  std::string str()
  {
    if (_has_changed)
    {
      for (auto &e : _css)
      {
        _str += e.first + "{";
        for (auto &p : e.second)
        {
          _str += p.first + ":" + p.second + ";";
        }
        _str += "}";
      }
      _has_changed = false;
    }
    return _str;
  }

private:
  bool _has_changed {false};
  std::string _str;
  std::map<std::string, std::multimap<std::string, std::string>> _css;
}; // class Css

class Js
{
public:
  std::string str() const
  {
    return str_;
  }

  Js& operator()(std::string const s)
  {
    str_ += s;
    return *this;
  }

private:
  std::string str_;
}; // class Js

} // namespace Html
} // namespace OB

#endif // OB_HTML_HH
