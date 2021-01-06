open MaterialUi;

let listToReactArray = xs => xs->Belt.List.toArray->React.array;

module Hook = (Fetcher: Http.Fetcher) => {
  module API = RemoteApi.API(Http.BsFetch);

  let decode =
      (json: Js.Json.t): Belt.Result.t(WebReport.Report_bs.report, string) => {
    json->Report_bs.read_report->Ok;
  };

  let use = () => {
    API.Hook.useGet(decode);
  };
};

module ReportEntryTH = {
  [@react.component]
  let make = (~depth) => {
    <TableHead>
      <TableRow>
        {{
           Belt.List.make(depth, ())
           ->Belt.List.mapWithIndex((i, _) =>
               <TableCell key={i->string_of_int}>
                 <b> {("T-" ++ (depth - i)->string_of_int)->React.string} </b>
               </TableCell>
             )
           ->Belt.List.concat([
               <TableCell key="tags">
                 <b> "Tags"->React.string </b>
               </TableCell>,
             ])
           ->Belt.List.add(
               <TableCell key="ta"> <b> "TA"->React.string </b> </TableCell>,
             )
           ->Belt.List.add(
               <TableCell key="period">
                 <b> "Period"->React.string </b>
               </TableCell>,
             )
           ->Belt.List.add(
               <TableCell key="name">
                 <b> "Name"->React.string </b>
               </TableCell>,
             );
         }
         ->listToReactArray}
      </TableRow>
    </TableHead>;
  };
};

let getRowStyle = (index: int) => {
  ReactDOM.Style.make(
    ~backgroundColor={
      index mod 2 == 0 ? "Ivory" : "WhiteSmoke";
    },
    (),
  );
};

module PriceReportTR = {
  [@react.component]
  let make =
      (
        ~name: string,
        ~period: string,
        ~data: WebReport.Report_t.price_report_entry,
        ~url: string,
        ~index: int,
      ) => {
    <TableRow style={getRowStyle(index)}>
      {{
         data.periods
         ->Belt.List.mapWithIndex((i, e) =>
             <TableCell key={i->string_of_int}>
               {e->Js.Float.toString->React.string}
             </TableCell>
           )
         ->Belt.List.concat([<TableCell key="tag" />])
         ->Belt.List.add(
             <TableCell key="ta"> "Price"->React.string </TableCell>,
           )
         ->Belt.List.add(
             <TableCell key="period"> period->React.string </TableCell>,
           )
         ->Belt.List.add(
             <TableCell key="name">
               <a href=url> name->React.string </a>
             </TableCell>,
           );
       }
       ->listToReactArray}
    </TableRow>;
  };
};

module MACDReportTR = {
  let gbToString = (gb: WebReport.Report_t.gb): string =>
    switch (gb) {
    | `BAD => "BAD"
    | `GOOD => "GOOD"
    };
  let gbToColor = (gb: WebReport.Report_t.gb) =>
    switch (gb) {
    | `BAD => `Secondary
    | `GOOD => `Primary
    };

  [@react.component]
  let make =
      (
        ~name: string,
        ~period: string,
        ~data: WebReport.Report_t.macd_report_entry,
        ~url: string,
        ~index: int,
      ) => {
    let cs =
      <Chip
        variant=`Outlined
        size=`Small
        avatar={<Avatar> "CS"->React.string </Avatar>}
        label={data.cs->string_of_int->React.string}
        color=`Primary
      />;
    let momentum =
      <Chip
        variant=`Outlined
        size=`Small
        avatar={<Avatar> "M"->React.string </Avatar>}
        label={data.momentum->gbToString->React.string}
        color={data.momentum->gbToColor}
      />;
    <TableRow style={getRowStyle(index)}>
      {{
         data.periods
         ->Belt.List.mapWithIndex((i, e) =>
             <TableCell key={i->string_of_int}>
               {"D/"
                ++ {
                  e.diff->Js.Float.toFixedWithPrecision(~digits=5);
                }
                ++ " M/"
                ++ {
                  e.macd_line->Js.Float.toFixedWithPrecision(~digits=5);
                }}
             </TableCell>
           )
         ->Belt.List.concat([
             <TableCell key="tag">
               <Grid container=true> <Grid item=true> cs </Grid> </Grid>
               <Grid container=true> <Grid item=true> momentum </Grid> </Grid>
             </TableCell>,
           ])
         ->Belt.List.add(
             <TableCell key="ta"> "MACD"->React.string </TableCell>,
           )
         ->Belt.List.add(
             <TableCell key="period"> period->React.string </TableCell>,
           )
         ->Belt.List.add(
             <TableCell key="name">
               <a href=url> name->React.string </a>
             </TableCell>,
           );
       }
       ->listToReactArray}
    </TableRow>;
  };
};

module PairTRs = {
  let period_to_string = (period: WebReport.Report_t.period): string =>
    switch (period) {
    | `ONE_H => "1H"
    | `ONE_D => "1D"
    };

  [@react.component]
  let make = (~pdata: WebReport.Report_t.report_entry, ~index: int) =>
    {
      switch (pdata.data) {
      | `SUCCESS(re) => [
          <PriceReportTR
            key="price"
            name={pdata.pair}
            period={pdata.period->period_to_string}
            data={re.price}
            url={pdata.url}
            index
          />,
          <MACDReportTR
            key="macd"
            name={pdata.pair}
            period={pdata.period->period_to_string}
            data={re.macd}
            url={pdata.url}
            index
          />,
        ]
      | `ERROR(err) => [
          <TableRow> <TableCell> err->React.string </TableCell> </TableRow>,
        ]
      };
    }
    ->listToReactArray;
};

module ReportTable = {
  let getPairList =
      (data: list(WebReport.Report_t.report_entry)): list(string) => {
    data
    ->Belt.List.map(e => e.pair)
    ->Belt.List.reduce([], (acc, e) =>
        acc->Belt.List.has(e, (==)) ? acc : acc->Belt.List.add(e)
      );
  };

  let filterReportEntryByName =
      (data: list(WebReport.Report_t.report_entry), name: string)
      : list(WebReport.Report_t.report_entry) => {
    data->Belt.List.keep(e => String.equal(e.pair, name));
  };
  [@react.component]
  let make = (~data: list(WebReport.Report_t.report_entry)) => {
    <Box
      border={Box.Value.int(1)}
      borderColor={Box.Value.paletteColor(Box.PaletteColor.primary_light)}>
      <Table size=`Small>
        <ReportEntryTH depth={data->Belt.List.getExn(0).depth} />
        <TableBody>
          {data
           ->getPairList
           ->Belt.List.mapWithIndex((i, pname) =>
               data
               ->filterReportEntryByName(pname)
               ->Belt.List.mapWithIndex((j, pdata) =>
                   <PairTRs index=i key={pname ++ j->string_of_int} pdata />
                 )
             )
           ->Belt.List.flatten
           ->listToReactArray}
        </TableBody>
      </Table>
    </Box>;
  };
};

module Main = (Fetcher: Http.Fetcher) => {
  module Hook' = Hook(Fetcher);

  let getHRDateFromEpoch = (epoch: float) => {
    Js.Date.fromFloat(epoch *. 1000.)->Js.Date.toUTCString;
  };

  [@react.component]
  let make = () => {
    let (state, cb, _) = Hook'.use();
    let url = "report.json";
    switch (state) {
    | NotAsked => cb(url)
    | _ => ()
    };
    switch (state) {
    | NotAsked
    | Loading(_) => React.null
    | Success(data) =>
      <Container>
        <Grid container=true>
          <Grid item=true>
            <Typography variant=`H3 gutterBottom=true>
              "BBot Report"->React.string
            </Typography>
            <Typography variant=`H6 gutterBottom=true>
              {("Generated at: " ++ data.epoch->getHRDateFromEpoch)
               ->React.string}
            </Typography>
          </Grid>
          <Grid item=true> <ReportTable data={data.report} /> </Grid>
        </Grid>
      </Container>
    | Failure(_) => <p> "Failure loading report"->React.string </p>
    };
  };
};
