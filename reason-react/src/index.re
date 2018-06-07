[%%debugger.chrome]

open ReactDOMRe;

type resultType =
  | Loading
  | Success(string)
  | Error(string);

type debugExampleType = {
  name: string,
  value: float,
  result: resultType,
};

let example1 = {name: "Test 1", value: 1.2, result: Loading};

let example2 = {
  name: "Test 2",
  value: 10.1,
  result: Success("THE RESULT VALUE"),
};

Js.log(example1);

Js.log(example2);

renderToElementWithId(<App />, "root");