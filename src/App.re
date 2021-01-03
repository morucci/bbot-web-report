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

module Main = (Fetcher: Http.Fetcher) => {
  module Hook' = Hook(Fetcher);
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
      <p>
        {("Test app: " ++ data->Belt.List.length->string_of_int)->React.string}
      </p>
    | Failure(_) => <p> "Failure loading report"->React.string </p>
    };
  };
};
