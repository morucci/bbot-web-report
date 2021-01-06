(* Auto-generated from "report.atd" *)
              [@@@ocaml.warning "-27-32-35-39"]

type price_report_entry = Report_t.price_report_entry = {
  periods: float list
}

type macd_entry = Report_t.macd_entry = { diff: float; macd_line: float }

type gb = Report_t.gb

type macd_report_entry = Report_t.macd_report_entry = {
  periods: macd_entry list;
  cs: int;
  momentum: gb
}

type x_report_entry = Report_t.x_report_entry = {
  price: price_report_entry;
  macd: macd_report_entry
}

type x_report_entry_se = Report_t.x_report_entry_se

type period = Report_t.period

type report_entry = Report_t.report_entry = {
  data: x_report_entry_se;
  pair: string;
  url: string;
  depth: int;
  period: period
}

type report = Report_t.report = { report: report_entry list; epoch: float }

val read_price_report_entry :  price_report_entry Atdgen_codec_runtime.Decode.t

val write_price_report_entry :  price_report_entry Atdgen_codec_runtime.Encode.t

val read_macd_entry :  macd_entry Atdgen_codec_runtime.Decode.t

val write_macd_entry :  macd_entry Atdgen_codec_runtime.Encode.t

val read_gb :  gb Atdgen_codec_runtime.Decode.t

val write_gb :  gb Atdgen_codec_runtime.Encode.t

val read_macd_report_entry :  macd_report_entry Atdgen_codec_runtime.Decode.t

val write_macd_report_entry :  macd_report_entry Atdgen_codec_runtime.Encode.t

val read_x_report_entry :  x_report_entry Atdgen_codec_runtime.Decode.t

val write_x_report_entry :  x_report_entry Atdgen_codec_runtime.Encode.t

val read_x_report_entry_se :  x_report_entry_se Atdgen_codec_runtime.Decode.t

val write_x_report_entry_se :  x_report_entry_se Atdgen_codec_runtime.Encode.t

val read_period :  period Atdgen_codec_runtime.Decode.t

val write_period :  period Atdgen_codec_runtime.Encode.t

val read_report_entry :  report_entry Atdgen_codec_runtime.Decode.t

val write_report_entry :  report_entry Atdgen_codec_runtime.Encode.t

val read_report :  report Atdgen_codec_runtime.Decode.t

val write_report :  report Atdgen_codec_runtime.Encode.t

