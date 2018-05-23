type player = [ | `X | `O];

type marker = [ player | `NoMarker];

type state = {cells: array(marker)};

type cellIndex = int;

type action =
  | PlaceMarker(cellIndex)
  | ResetState;

type gameState =
  | Active(player)
  | Tie
  | Won(player);

let initialState = () => {
  cells: [|
    `NoMarker,
    `NoMarker,
    `NoMarker,
    `NoMarker,
    `NoMarker,
    `NoMarker,
    `NoMarker,
    `NoMarker,
    `NoMarker,
  |],
};

let stringOfMarker = marker =>
  switch (marker) {
  | `X => "X"
  | `O => "O"
  | `NoMarker => ""
  };

let detectCurrentPlayerTurn = state => {
  let xCount =
    Array.fold_left((a, b) => b === `X ? a + 1 : a, 0, state.cells);
  let oCount =
    Array.fold_left((a, b) => b === `O ? a + 1 : a, 0, state.cells);
  xCount > oCount ? `O : `X;
};

let directions = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6],
];

let detectGameState = state => {
  let rows =
    List.map(dir => List.map(index => state.cells[index], dir), directions);
  let winningRow =
    Belt.List.getBy(rows, row =>
      switch (row) {
      | [`X, `X, `X] => true
      | [`O, `O, `O] => true
      | _ => false
      }
    );
  switch (winningRow) {
  | Some([`X, `X, `X]) => Won(`X)
  | Some([`O, `O, `O]) => Won(`O)
  | _ => Active(detectCurrentPlayerTurn(state))
  };
};

let component = ReasonReact.reducerComponent("GameState");

type renderState = {
  state,
  gameState,
  placeMarker: int => unit,
  resetState: unit => unit,
};

let isMoveAllowed = (cellIndex, state) =>
  switch (detectGameState(state)) {
  | Active(_currentPlayer) =>
    switch (state.cells[cellIndex]) {
    | `NoMarker => true
    | _ => false
    }
  | _ => false
  };

let make = (~render, _children) => {
  ...component,
  initialState,
  reducer: (action, state) =>
    switch (action) {
    | PlaceMarker(cellIndex) when isMoveAllowed(cellIndex, state) =>
      let cells = Array.copy(state.cells);
      cells[cellIndex] = detectCurrentPlayerTurn(state);
      ReasonReact.Update({cells: cells});
    | PlaceMarker(_index) => ReasonReact.NoUpdate
    | ResetState => ReasonReact.Update(initialState())
    },
  render: self =>
    render({
      state: self.state,
      gameState: detectGameState(self.state),
      resetState: () => self.send(ResetState),
      placeMarker: index => self.send(PlaceMarker(index)),
    }),
};