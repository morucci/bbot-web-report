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

let write__1 = (
  Atdgen_codec_runtime.Encode.list (
    Atdgen_codec_runtime.Encode.float
  )
)
let read__1 = (
  Atdgen_codec_runtime.Decode.list (
    Atdgen_codec_runtime.Decode.float
  )
)
let write_price_report_entry = (
  Atdgen_codec_runtime.Encode.make (fun (t : price_report_entry) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            write__1
            )
          ~name:"periods"
          t.periods
      ]
    )
  )
)
let read_price_report_entry = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          periods =
            Atdgen_codec_runtime.Decode.decode
            (
              read__1
              |> Atdgen_codec_runtime.Decode.field "periods"
            ) json;
      } : price_report_entry)
    )
  )
)
let write_macd_entry = (
  Atdgen_codec_runtime.Encode.make (fun (t : macd_entry) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.float
            )
          ~name:"diff"
          t.diff
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.float
            )
          ~name:"macd_line"
          t.macd_line
      ]
    )
  )
)
let read_macd_entry = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          diff =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.float
              |> Atdgen_codec_runtime.Decode.field "diff"
            ) json;
          macd_line =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.float
              |> Atdgen_codec_runtime.Decode.field "macd_line"
            ) json;
      } : macd_entry)
    )
  )
)
let write_gb = (
  Atdgen_codec_runtime.Encode.make (fun (x : _) -> match x with
    | `GOOD ->
    Atdgen_codec_runtime.Encode.constr0 "GOOD"
    | `BAD ->
    Atdgen_codec_runtime.Encode.constr0 "BAD"
  )
)
let read_gb = (
  Atdgen_codec_runtime.Decode.enum
  [
      (
      "GOOD"
      ,
        `Single (`GOOD)
      )
    ;
      (
      "BAD"
      ,
        `Single (`BAD)
      )
  ]
)
let write__2 = (
  Atdgen_codec_runtime.Encode.list (
    write_macd_entry
  )
)
let read__2 = (
  Atdgen_codec_runtime.Decode.list (
    read_macd_entry
  )
)
let write_macd_report_entry = (
  Atdgen_codec_runtime.Encode.make (fun (t : macd_report_entry) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            write__2
            )
          ~name:"periods"
          t.periods
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.int
            )
          ~name:"cs"
          t.cs
        ;
          Atdgen_codec_runtime.Encode.field
            (
            write_gb
            )
          ~name:"momentum"
          t.momentum
      ]
    )
  )
)
let read_macd_report_entry = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          periods =
            Atdgen_codec_runtime.Decode.decode
            (
              read__2
              |> Atdgen_codec_runtime.Decode.field "periods"
            ) json;
          cs =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.int
              |> Atdgen_codec_runtime.Decode.field "cs"
            ) json;
          momentum =
            Atdgen_codec_runtime.Decode.decode
            (
              read_gb
              |> Atdgen_codec_runtime.Decode.field "momentum"
            ) json;
      } : macd_report_entry)
    )
  )
)
let write_x_report_entry = (
  Atdgen_codec_runtime.Encode.make (fun (t : x_report_entry) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            write_price_report_entry
            )
          ~name:"price"
          t.price
        ;
          Atdgen_codec_runtime.Encode.field
            (
            write_macd_report_entry
            )
          ~name:"macd"
          t.macd
      ]
    )
  )
)
let read_x_report_entry = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          price =
            Atdgen_codec_runtime.Decode.decode
            (
              read_price_report_entry
              |> Atdgen_codec_runtime.Decode.field "price"
            ) json;
          macd =
            Atdgen_codec_runtime.Decode.decode
            (
              read_macd_report_entry
              |> Atdgen_codec_runtime.Decode.field "macd"
            ) json;
      } : x_report_entry)
    )
  )
)
let write_x_report_entry_se = (
  Atdgen_codec_runtime.Encode.make (fun (x : _) -> match x with
    | `SUCCESS x ->
    Atdgen_codec_runtime.Encode.constr1 "SUCCESS" (
      write_x_report_entry
    ) x
    | `ERROR x ->
    Atdgen_codec_runtime.Encode.constr1 "ERROR" (
      Atdgen_codec_runtime.Encode.string
    ) x
  )
)
let read_x_report_entry_se = (
  Atdgen_codec_runtime.Decode.enum
  [
      (
      "SUCCESS"
      ,
        `Decode (
        read_x_report_entry
        |> Atdgen_codec_runtime.Decode.map (fun x -> ((`SUCCESS x) : _))
        )
      )
    ;
      (
      "ERROR"
      ,
        `Decode (
        Atdgen_codec_runtime.Decode.string
        |> Atdgen_codec_runtime.Decode.map (fun x -> ((`ERROR x) : _))
        )
      )
  ]
)
let write_period = (
  Atdgen_codec_runtime.Encode.make (fun (x : _) -> match x with
    | `ONE_H ->
    Atdgen_codec_runtime.Encode.constr0 "ONE_H"
    | `ONE_D ->
    Atdgen_codec_runtime.Encode.constr0 "ONE_D"
  )
)
let read_period = (
  Atdgen_codec_runtime.Decode.enum
  [
      (
      "ONE_H"
      ,
        `Single (`ONE_H)
      )
    ;
      (
      "ONE_D"
      ,
        `Single (`ONE_D)
      )
  ]
)
let write_report_entry = (
  Atdgen_codec_runtime.Encode.make (fun (t : report_entry) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            write_x_report_entry_se
            )
          ~name:"data"
          t.data
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.string
            )
          ~name:"pair"
          t.pair
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.string
            )
          ~name:"url"
          t.url
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.int
            )
          ~name:"depth"
          t.depth
        ;
          Atdgen_codec_runtime.Encode.field
            (
            write_period
            )
          ~name:"period"
          t.period
      ]
    )
  )
)
let read_report_entry = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          data =
            Atdgen_codec_runtime.Decode.decode
            (
              read_x_report_entry_se
              |> Atdgen_codec_runtime.Decode.field "data"
            ) json;
          pair =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.string
              |> Atdgen_codec_runtime.Decode.field "pair"
            ) json;
          url =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.string
              |> Atdgen_codec_runtime.Decode.field "url"
            ) json;
          depth =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.int
              |> Atdgen_codec_runtime.Decode.field "depth"
            ) json;
          period =
            Atdgen_codec_runtime.Decode.decode
            (
              read_period
              |> Atdgen_codec_runtime.Decode.field "period"
            ) json;
      } : report_entry)
    )
  )
)
let write__3 = (
  Atdgen_codec_runtime.Encode.list (
    write_report_entry
  )
)
let read__3 = (
  Atdgen_codec_runtime.Decode.list (
    read_report_entry
  )
)
let write_report = (
  Atdgen_codec_runtime.Encode.make (fun (t : report) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            write__3
            )
          ~name:"report"
          t.report
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.float
            )
          ~name:"epoch"
          t.epoch
      ]
    )
  )
)
let read_report = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          report =
            Atdgen_codec_runtime.Decode.decode
            (
              read__3
              |> Atdgen_codec_runtime.Decode.field "report"
            ) json;
          epoch =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.float
              |> Atdgen_codec_runtime.Decode.field "epoch"
            ) json;
      } : report)
    )
  )
)
