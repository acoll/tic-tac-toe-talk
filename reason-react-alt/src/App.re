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
           (~board, ~player, ~winner, ~placeMarker) =>
             <Fragment>
              (switch(winner) {
               | None => <header> (ReasonReact.string(player ++ "'s Turn")) </header>
               | Some(player) => <header className="active"> (ReasonReact.string(player ++ " won!")) </header>
               })
               <Board board placeMarker />
             </Fragment>
         )
    </GameState>,
};