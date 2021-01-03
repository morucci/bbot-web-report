'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Http$WebReport = require("./Http.bs.js");
var RemoteApi$WebReport = require("./RemoteApi.bs.js");
var Report_bs$WebReport = require("./report_bs.bs.js");

function Hook(Fetcher) {
  var API = RemoteApi$WebReport.API({
        $$fetch: Http$WebReport.BsFetch.$$fetch
      });
  var decode = function (json) {
    return {
            TAG: /* Ok */0,
            _0: Report_bs$WebReport.read_report(json)
          };
  };
  var use = function (param) {
    return Curry._1(API.Hook.useGet, decode);
  };
  return {
          API: API,
          decode: decode,
          use: use
        };
}

function Main(Fetcher) {
  var API = RemoteApi$WebReport.API({
        $$fetch: Http$WebReport.BsFetch.$$fetch
      });
  var decode = function (json) {
    return {
            TAG: /* Ok */0,
            _0: Report_bs$WebReport.read_report(json)
          };
  };
  var use = function (param) {
    return Curry._1(API.Hook.useGet, decode);
  };
  var Hook$prime = {
    API: API,
    decode: decode,
    use: use
  };
  var App$Main = function (Props) {
    var match = Curry._1(API.Hook.useGet, decode);
    var state = match[0];
    if (typeof state === "number") {
      Curry._1(match[1], "report.json");
    }
    if (typeof state === "number") {
      return null;
    }
    switch (state.TAG | 0) {
      case /* Loading */0 :
          return null;
      case /* Failure */1 :
          return React.createElement("p", undefined, "Failure loading report");
      case /* Success */2 :
          return React.createElement("p", undefined, "Test app: " + String(Belt_List.length(state._0)));
      
    }
  };
  return {
          Hook$prime: Hook$prime,
          make: App$Main
        };
}

exports.Hook = Hook;
exports.Main = Main;
/* react Not a pure module */
