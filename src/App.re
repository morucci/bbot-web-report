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
                 {("T-" ++ (depth - i)->string_of_int)->React.string}
               </TableCell>
             );
         }
         ->listToReactArray}
      </TableRow>
    </TableHead>;
  };
};

module PriceReportEntry = {
  [@react.component]
  let make = (~data: WebReport.Report_t.price_report_entry) => {
    let depth = data.periods->Belt.List.length;
    <Card>
      <CardContent>
        <Typography color=`Initial variant=`Subtitle2>
          "Price"->React.string
        </Typography>
        <TableContainer>
          <Table size=`Small>
            <ReportEntryTH depth />
            <TableBody>
              <TableRow>
                {{
                   data.periods
                   ->Belt.List.mapWithIndex((i, e) =>
                       <TableCell key={i->string_of_int}>
                         {e->Js.Float.toString->React.string}
                       </TableCell>
                     );
                 }
                 ->listToReactArray}
              </TableRow>
            </TableBody>
          </Table>
        </TableContainer>
      </CardContent>
    </Card>;
  };
};

module MACDReportEntry = {
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
  let make = (~data: WebReport.Report_t.macd_report_entry) => {
    let depth = data.periods->Belt.List.length;
    <Card>
      <CardContent>
        <Typography color=`Initial variant=`Subtitle2>
          "MACD"->React.string
        </Typography>
        <Grid container=true spacing=`V1 justify=`Space_Around>
          <Grid item=true>
            <Chip
              variant=`Outlined
              size=`Small
              avatar={<Avatar> "CS"->React.string </Avatar>}
              label={data.cs->string_of_int->React.string}
              color=`Primary
            />
          </Grid>
          <Grid item=true>
            <Chip
              variant=`Outlined
              size=`Small
              avatar={<Avatar> "M"->React.string </Avatar>}
              label={data.momentum->gbToString->React.string}
              color={data.momentum->gbToColor}
            />
          </Grid>
        </Grid>
        <TableContainer>
          <Table size=`Small>
            <ReportEntryTH depth />
            <TableBody>
              <TableRow>
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
                            e.macd_line
                            ->Js.Float.toFixedWithPrecision(~digits=5);
                          }}
                       </TableCell>
                     );
                 }
                 ->listToReactArray}
              </TableRow>
            </TableBody>
          </Table>
        </TableContainer>
      </CardContent>
    </Card>;
  };
};

module PairPeriod = {
  let period_to_string = (period: WebReport.Report_t.period): string =>
    switch (period) {
    | `ONE_H => "Period: 1H"
    | `ONE_D => "Period: 1D"
    };

  [@react.component]
  let make = (~pdata: WebReport.Report_t.report_entry) => {
    <Grid item=true>
      <Card>
        <CardContent>
          <Typography color=`Primary variant=`Subtitle1>
            {pdata.period->period_to_string->React.string}
          </Typography>
          {switch (pdata.data) {
           | `SUCCESS(re) =>
             <Grid
               container=true
               direction=`Column
               spacing=`V2
               justify=`Space_Around>
               <Grid item=true> <PriceReportEntry data={re.price} /> </Grid>
               <Grid item=true> <MACDReportEntry data={re.macd} /> </Grid>
             </Grid>
           | `ERROR(err) => <p> err->React.string </p>
           }}
        </CardContent>
      </Card>
    </Grid>;
  };
};

module Pair = {
  [@react.component]
  let make = (~name: string, ~data: list(WebReport.Report_t.report_entry)) => {
    <Grid item=true>
      <Box
        border={Box.Value.int(1)}
        borderColor={Box.Value.paletteColor(Box.PaletteColor.primary_light)}>
        <Typography color=`Primary variant=`H6>
          name->React.string
        </Typography>
        <Grid
          container=true direction=`Column spacing=`V2 justify=`Space_Around>
          {data
           ->Belt.List.mapWithIndex((i, pdata) =>
               <PairPeriod key={i->string_of_int} pdata />
             )
           ->listToReactArray}
        </Grid>
      </Box>
    </Grid>;
  };
};

module Main = (Fetcher: Http.Fetcher) => {
  module Hook' = Hook(Fetcher);

  let getPairList = (data: WebReport.Report_t.report): list(string) => {
    data
    ->Belt.List.map(e => e.pair)
    ->Belt.List.reduce([], (acc, e) =>
        acc->Belt.List.has(e, (==)) ? acc : acc->Belt.List.add(e)
      );
  };

  let filterReportEntryByName =
      (name: string, data: WebReport.Report_t.report)
      : list(WebReport.Report_t.report_entry) => {
    data->Belt.List.keep(e => String.equal(e.pair, name));
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
        <Typography variant=`H3 gutterBottom=true>
          "BBot Report"->React.string
        </Typography>
        <Grid
          container=true direction=`Column spacing=`V2 justify=`Space_Around>
          {{
             data
             ->getPairList
             ->Belt.List.map(name =>
                 <Pair
                   key=name
                   name
                   data={filterReportEntryByName(name, data)}
                 />
               );
           }
           ->listToReactArray}
        </Grid>
      </Container>
    | Failure(_) => <p> "Failure loading report"->React.string </p>
    };
  };
};
