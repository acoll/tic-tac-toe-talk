type player =
  | X
  | O;

type board = array(option(player));

type state = {
  player,
  board,
};

type action =
  | Claim(int);

let component = ReasonReact.reducerComponent("GameState");

let placeMarker =
    (
      self: ReasonReact.self(state, ReasonReact.noRetainedProps, action),
      index,
    ) =>
  self.send(Claim(index));

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

  let winner =
    Belt.List.reduce(
      Belt.List.map(
        Belt.List.map(combinations, combination =>
          Belt.List.map(combination, boardIndex =>
            Belt.Array.getExn(board, boardIndex)
          )
        ),
        cells =>
        Belt.List.reduce(cells, Belt.List.getExn(cells, 0), (a, b) =>
          switch (a, b) {
          | (Some(X), Some(X)) => Some(X)
          | (Some(O), Some(O)) => Some(O)
          | _ => None
          }
        )
      ),
      None,
      (a, b) =>
      switch (a, b) {
      | (Some(X), _) => Some(X)
      | (_, Some(X)) => Some(X)
      | (Some(O), _) => Some(O)
      | (_, Some(O)) => Some(O)
      | _ => None
      }
    );

  switch (winner) {
  | None => None
  | Some(player) => Some(playerToString(player))
  };
};

let make = children => {
  ...component,
  initialState: () => {
    player: X,
    board: [|None, None, None, None, None, None, None, None, None|],
  },
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
    },
  render: self =>
    children(
      ~board=self.state.board: board,
      ~player=playerToString(self.state.player),
      ~winner=checkForWinner(self.state.board),
      ~placeMarker=placeMarker(self),
    ),
};