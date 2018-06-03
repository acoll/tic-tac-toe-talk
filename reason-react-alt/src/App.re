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
           (~board, ~player, ~winner, ~isTie, ~placeMarker, ~reset) =>
             <Fragment>
               (
                 switch (winner) {
                 | None =>
                   if (isTie) {
                     <header className="active">
                       (ReasonReact.string("Tie Game"))
                     </header>;
                   } else {
                     <header>
                       (ReasonReact.string(player ++ "'s Turn"))
                     </header>;
                   }
                 | Some(player) =>
                   <header className="active">
                     (ReasonReact.string(player ++ " won!"))
                   </header>
                 }
               )
               <button onClick=reset> (ReasonReact.string("reset")) </button>
               <Board board placeMarker />
             </Fragment>
         )
    </GameState>,
};