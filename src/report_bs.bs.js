'use strict';

var Atdgen_codec_runtime = require("@ahrefs/bs-atdgen-codec-runtime/src/atdgen_codec_runtime.bs.js");

function write__1(param) {
  return Atdgen_codec_runtime.Encode.list(Atdgen_codec_runtime.Encode.$$float, param);
}

function read__1(param) {
  return Atdgen_codec_runtime.Decode.list(Atdgen_codec_runtime.Decode.$$float, param);
}

var write_price_report_entry = Atdgen_codec_runtime.Encode.make(function (t) {
      return Atdgen_codec_runtime.Encode.obj({
                  hd: Atdgen_codec_runtime.Encode.field(undefined, write__1, "periods", t.periods),
                  tl: /* [] */0
                });
    });

var read_price_report_entry = Atdgen_codec_runtime.Decode.make(function (json) {
      return {
              periods: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("periods", read__1, param);
                    }), json)
            };
    });

var write_macd_entry = Atdgen_codec_runtime.Encode.make(function (t) {
      return Atdgen_codec_runtime.Encode.obj({
                  hd: Atdgen_codec_runtime.Encode.field(undefined, Atdgen_codec_runtime.Encode.$$float, "diff", t.diff),
                  tl: {
                    hd: Atdgen_codec_runtime.Encode.field(undefined, Atdgen_codec_runtime.Encode.$$float, "macd_line", t.macd_line),
                    tl: /* [] */0
                  }
                });
    });

var read_macd_entry = Atdgen_codec_runtime.Decode.make(function (json) {
      return {
              diff: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("diff", Atdgen_codec_runtime.Decode.$$float, param);
                    }), json),
              macd_line: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("macd_line", Atdgen_codec_runtime.Decode.$$float, param);
                    }), json)
            };
    });

var write_gb = Atdgen_codec_runtime.Encode.make(function (x) {
      if (x === "GOOD") {
        return Atdgen_codec_runtime.Encode.constr0("GOOD");
      } else {
        return Atdgen_codec_runtime.Encode.constr0("BAD");
      }
    });

var partial_arg = {
  hd: [
    "GOOD",
    {
      NAME: "Single",
      VAL: "GOOD"
    }
  ],
  tl: {
    hd: [
      "BAD",
      {
        NAME: "Single",
        VAL: "BAD"
      }
    ],
    tl: /* [] */0
  }
};

function read_gb(param) {
  return Atdgen_codec_runtime.Decode.$$enum(partial_arg, param);
}

function write__2(param) {
  return Atdgen_codec_runtime.Encode.list(write_macd_entry, param);
}

function read__2(param) {
  return Atdgen_codec_runtime.Decode.list(read_macd_entry, param);
}

var write_macd_report_entry = Atdgen_codec_runtime.Encode.make(function (t) {
      return Atdgen_codec_runtime.Encode.obj({
                  hd: Atdgen_codec_runtime.Encode.field(undefined, write__2, "periods", t.periods),
                  tl: {
                    hd: Atdgen_codec_runtime.Encode.field(undefined, Atdgen_codec_runtime.Encode.$$int, "cs", t.cs),
                    tl: {
                      hd: Atdgen_codec_runtime.Encode.field(undefined, write_gb, "momentum", t.momentum),
                      tl: /* [] */0
                    }
                  }
                });
    });

var read_macd_report_entry = Atdgen_codec_runtime.Decode.make(function (json) {
      return {
              periods: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("periods", read__2, param);
                    }), json),
              cs: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("cs", Atdgen_codec_runtime.Decode.$$int, param);
                    }), json),
              momentum: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("momentum", read_gb, param);
                    }), json)
            };
    });

var write_x_report_entry = Atdgen_codec_runtime.Encode.make(function (t) {
      return Atdgen_codec_runtime.Encode.obj({
                  hd: Atdgen_codec_runtime.Encode.field(undefined, write_price_report_entry, "price", t.price),
                  tl: {
                    hd: Atdgen_codec_runtime.Encode.field(undefined, write_macd_report_entry, "macd", t.macd),
                    tl: /* [] */0
                  }
                });
    });

var read_x_report_entry = Atdgen_codec_runtime.Decode.make(function (json) {
      return {
              price: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("price", read_price_report_entry, param);
                    }), json),
              macd: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("macd", read_macd_report_entry, param);
                    }), json)
            };
    });

var write_x_report_entry_se = Atdgen_codec_runtime.Encode.make(function (x) {
      if (x.NAME === "SUCCESS") {
        return Atdgen_codec_runtime.Encode.constr1("SUCCESS", write_x_report_entry, x.VAL);
      } else {
        return Atdgen_codec_runtime.Encode.constr1("ERROR", Atdgen_codec_runtime.Encode.string, x.VAL);
      }
    });

var partial_arg_0 = [
  "SUCCESS",
  {
    NAME: "Decode",
    VAL: (function (param) {
        return Atdgen_codec_runtime.Decode.map((function (x) {
                      return {
                              NAME: "SUCCESS",
                              VAL: x
                            };
                    }), read_x_report_entry, param);
      })
  }
];

var partial_arg_1 = {
  hd: [
    "ERROR",
    {
      NAME: "Decode",
      VAL: (function (param) {
          return Atdgen_codec_runtime.Decode.map((function (x) {
                        return {
                                NAME: "ERROR",
                                VAL: x
                              };
                      }), Atdgen_codec_runtime.Decode.string, param);
        })
    }
  ],
  tl: /* [] */0
};

var partial_arg$1 = {
  hd: partial_arg_0,
  tl: partial_arg_1
};

function read_x_report_entry_se(param) {
  return Atdgen_codec_runtime.Decode.$$enum(partial_arg$1, param);
}

var write_period = Atdgen_codec_runtime.Encode.make(function (x) {
      if (x === "ONE_H") {
        return Atdgen_codec_runtime.Encode.constr0("ONE_H");
      } else {
        return Atdgen_codec_runtime.Encode.constr0("ONE_D");
      }
    });

var partial_arg$2 = {
  hd: [
    "ONE_H",
    {
      NAME: "Single",
      VAL: "ONE_H"
    }
  ],
  tl: {
    hd: [
      "ONE_D",
      {
        NAME: "Single",
        VAL: "ONE_D"
      }
    ],
    tl: /* [] */0
  }
};

function read_period(param) {
  return Atdgen_codec_runtime.Decode.$$enum(partial_arg$2, param);
}

var write_report_entry = Atdgen_codec_runtime.Encode.make(function (t) {
      return Atdgen_codec_runtime.Encode.obj({
                  hd: Atdgen_codec_runtime.Encode.field(undefined, write_x_report_entry_se, "data", t.data),
                  tl: {
                    hd: Atdgen_codec_runtime.Encode.field(undefined, Atdgen_codec_runtime.Encode.string, "pair", t.pair),
                    tl: {
                      hd: Atdgen_codec_runtime.Encode.field(undefined, Atdgen_codec_runtime.Encode.$$int, "depth", t.depth),
                      tl: {
                        hd: Atdgen_codec_runtime.Encode.field(undefined, write_period, "period", t.period),
                        tl: /* [] */0
                      }
                    }
                  }
                });
    });

var read_report_entry = Atdgen_codec_runtime.Decode.make(function (json) {
      return {
              data: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("data", read_x_report_entry_se, param);
                    }), json),
              pair: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("pair", Atdgen_codec_runtime.Decode.string, param);
                    }), json),
              depth: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("depth", Atdgen_codec_runtime.Decode.$$int, param);
                    }), json),
              period: Atdgen_codec_runtime.Decode.decode((function (param) {
                      return Atdgen_codec_runtime.Decode.field("period", read_period, param);
                    }), json)
            };
    });

function write__3(param) {
  return Atdgen_codec_runtime.Encode.list(write_report_entry, param);
}

function read__3(param) {
  return Atdgen_codec_runtime.Decode.list(read_report_entry, param);
}

var read_report = read__3;

var write_report = write__3;

exports.read_price_report_entry = read_price_report_entry;
exports.write_price_report_entry = write_price_report_entry;
exports.read_macd_entry = read_macd_entry;
exports.write_macd_entry = write_macd_entry;
exports.read_gb = read_gb;
exports.write_gb = write_gb;
exports.read_macd_report_entry = read_macd_report_entry;
exports.write_macd_report_entry = write_macd_report_entry;
exports.read_x_report_entry = read_x_report_entry;
exports.write_x_report_entry = write_x_report_entry;
exports.read_x_report_entry_se = read_x_report_entry_se;
exports.write_x_report_entry_se = write_x_report_entry_se;
exports.read_period = read_period;
exports.write_period = write_period;
exports.read_report_entry = read_report_entry;
exports.write_report_entry = write_report_entry;
exports.read_report = read_report;
exports.write_report = write_report;
/* write_price_report_entry Not a pure module */
