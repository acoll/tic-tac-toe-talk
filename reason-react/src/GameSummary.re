open ReasonReact;

let component = statelessComponent("GameSummary");

let make = (_children, ~gameState: GameState.gameState) => {
  ...component,
  render: _self =>
    switch (gameState) {
    | Tie => <h1> (string("Tie Game!")) </h1>
    | Active(currentPlayer) =>
      <h3>
        (string(GameState.stringOfMarker(currentPlayer) ++ "'s Turn"))
      </h3>
    | Won(winner) =>
      <h1> (string(GameState.stringOfMarker(winner) ++ " Wins!")) </h1>
    },
};