'use strict';

var Js_exn = require("bs-platform/lib/js/js_exn.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function raiseOnNok(promise) {
  return promise.then(function (r) {
              if (r.ok) {
                return promise;
              } else {
                return Js_exn.raiseError(r.statusText);
              }
            });
}

function promiseToOptionalJson(promise) {
  return raiseOnNok(promise).then(function (prim) {
                  return prim.json();
                }).then(function (v) {
                return Promise.resolve(Caml_option.some(v));
              }).catch(function (e) {
              console.log("Unexpected error: ", e);
              return Promise.resolve(undefined);
            });
}

function $$fetch$1(url) {
  return promiseToOptionalJson(fetch(url));
}

var BsFetch = {
  raiseOnNok: raiseOnNok,
  promiseToOptionalJson: promiseToOptionalJson,
  $$fetch: $$fetch$1
};

exports.BsFetch = BsFetch;
/* No side effect */
