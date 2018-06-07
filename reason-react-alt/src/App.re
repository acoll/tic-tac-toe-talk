[%bs.raw {|require('../../../src/App.scss')|}];

type state = {score: int};

type action =
  | Click;

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <GameState>
      ...(
           (~board, ~player, ~gameState, ~placeMarker, ~playerToString, ~reset) =>
             <Fragment>
               (
                 switch (gameState) {
                 | Tie =>
                   <header className="active">
                     (ReasonReact.string("Tie Game"))
                   </header>
                 | Winner(player) =>
                   <header className="active">
                     (ReasonReact.string(playerToString(player) ++ " won!"))
                   </header>
                 | Incomplete =>
                   <header>
                     (
                       ReasonReact.string(playerToString(player) ++ "'s Turn")
                     )
                   </header>
                 }
               )
               <button onClick=reset> (ReasonReact.string("reset")) </button>
               <Board board placeMarker />
             </Fragment>
         )
    </GameState>,
};