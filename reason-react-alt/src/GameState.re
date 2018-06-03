type player =
  | X
  | O;

type board = array(option(player));

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

let checkForWinner = board => {
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

  switch (hasXWon, hasOWon) {
  | (true, false) => Some(playerToString(X))
  | (false, true) => Some(playerToString(O))
  | _ => None
  };
};

let isTie = board =>
  Belt.Array.reduce(board, true, (a, b) =>
    switch (a, b) {
    | (true, Some(_)) => true
    | _ => false
    }
  );

let make = children => {
  ...component,
  initialState,
  reducer: (action, state) =>
    switch (action) {
    | Claim(index) =>
      switch (
        checkForWinner(state.board),
        Belt.Array.getExn(state.board, index),
      ) {
      | (None, None) =>
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
      ~player=playerToString(self.state.player),
      ~winner=checkForWinner(self.state.board),
      ~isTie=isTie(self.state.board),
      ~placeMarker=placeMarker(self),
      ~reset=reset(self),
    ),
};