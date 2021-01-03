'use strict';

var React = require("react");
var ReactDom = require("react-dom");
var App$WebReport = require("./App.bs.js");
var Http$WebReport = require("./Http.bs.js");

var RealApp = App$WebReport.Main({
      $$fetch: Http$WebReport.BsFetch.$$fetch
    });

var root = document.querySelector("#root");

if (root == null) {
  console.log("Can't find #root element!");
} else {
  ReactDom.render(React.createElement(RealApp.make, {}), root);
}

exports.RealApp = RealApp;
/* RealApp Not a pure module */
