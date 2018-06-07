type player =
  | X
  | O;

type board = array(option(player));

type gameState =
  | Incomplete
  | Winner(player)
  | Tie;

type state = {
  player,
  board,
};

type action =
  | Claim(int)
  | Reset;

let component = ReasonReact.reducerComponent("GameState");

let placeMarker =
    (
      self: ReasonReact.self(state, ReasonReact.noRetainedProps, action),
      index,
    ) =>
  self.send(Claim(index));

let initialState = () => {
  player: X,
  board: [|None, None, None, None, None, None, None, None, None|],
};

let reset =
    (
      self: ReasonReact.self(state, ReasonReact.noRetainedProps, action),
      _event,
    ) =>
  self.send(Reset);

let playerToString = player =>
  switch (player) {
  | X => "X"
  | O => "O"
  };

let gameState = board => {
  let combinations = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];

  let actual =
    Belt.List.map(combinations, combination =>
      Belt.List.map(combination, index => board[index])
    );

  let hasXWon =
    Belt.List.some(actual, a => a == [Some(X), Some(X), Some(X)]);
  let hasOWon =
    Belt.List.some(actual, a => a == [Some(O), Some(O), Some(O)]);

  let isTie = board =>
    Belt.Array.reduce(board, true, (a, b) =>
      switch (a, b) {
      | (true, Some(_)) => true
      | _ => false
      }
    );

  switch (hasXWon, hasOWon, isTie(board)) {
  | (false, false, true) => Tie
  | (true, false, false) => Winner(X)
  | (false, true, false) => Winner(O)
  | _ => Incomplete
  };
};

let make = children => {
  ...component,
  initialState,
  reducer: (action, state) =>
    switch (action) {
    | Claim(index) =>
      switch (gameState(state.board), Belt.Array.getExn(state.board, index)) {
      | (Incomplete, None) =>
        Belt.Array.setExn(state.board, index, Some(state.player))
      | _ => ()
      };
      ReasonReact.Update({
        ...state,
        player:
          switch (state.player) {
          | X => O
          | O => X
          },
      });
    | Reset => ReasonReact.Update(initialState())
    },
  render: self =>
    children(
      ~board=self.state.board: board,
      ~player=self.state.player,
      ~gameState=gameState(self.state.board),
      ~placeMarker=placeMarker(self),
      ~playerToString,
      ~reset=reset(self),
    ),
};