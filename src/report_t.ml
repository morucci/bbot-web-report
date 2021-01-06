(* Auto-generated from "report.atd" *)
              [@@@ocaml.warning "-27-32-35-39"]

type price_report_entry = { periods: float list }

type macd_entry = { diff: float; macd_line: float }

type gb = [ `GOOD | `BAD ]

type cs = [ `UP of int | `DOWN of int ]

type macd_report_entry = { periods: macd_entry list; cs: cs; momentum: gb }

type x_report_entry = { price: price_report_entry; macd: macd_report_entry }

type x_report_entry_se = [ `SUCCESS of x_report_entry | `ERROR of string ]

type period = [ `ONE_H | `ONE_D ]

type report_entry = {
  data: x_report_entry_se;
  pair: string;
  url: string;
  depth: int;
  period: period
}

type report = { report: report_entry list; epoch: float }
