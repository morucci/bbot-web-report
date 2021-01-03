'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Result = require("bs-platform/lib/js/belt_Result.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function note(o, e) {
  if (o !== undefined) {
    return {
            TAG: /* Ok */0,
            _0: Caml_option.valFromOption(o)
          };
  } else {
    return {
            TAG: /* Error */1,
            _0: e
          };
  }
}

function API(Fetcher) {
  var get = function (url, decode, setState) {
    Curry._1(setState, {
          TAG: /* Loading */0,
          _0: undefined
        });
    return Curry._1(Fetcher.$$fetch, url).then(function (json) {
                var result = Belt_Result.flatMap(note(json, "Network error!"), Curry.__1(decode));
                var tmp;
                tmp = result.TAG === /* Ok */0 ? Curry._1(setState, {
                        TAG: /* Success */2,
                        _0: result._0
                      }) : Curry._1(setState, {
                        TAG: /* Failure */1,
                        _0: result._0
                      });
                return Promise.resolve({
                            TAG: /* Ok */0,
                            _0: tmp
                          });
              });
  };
  var useGet = function (decoder) {
    var match = React.useState(function () {
          return /* NotAsked */0;
        });
    var setState = match[1];
    var reset = function (param) {
      return Curry._1(setState, (function (_prevState) {
                    return /* NotAsked */0;
                  }));
    };
    var dispatch = function (url) {
      get(url, decoder, (function (r) {
              return Curry._1(setState, (function (_prevState) {
                            return r;
                          }));
            }));
      
    };
    return [
            match[0],
            dispatch,
            reset
          ];
  };
  var Hook = {
    useGet: useGet
  };
  return {
          get: get,
          Hook: Hook
        };
}

exports.note = note;
exports.API = API;
/* react Not a pure module */
