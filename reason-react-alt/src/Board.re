[%bs.raw {|require('../../../src/Board.scss')|}];

let component = ReasonReact.statelessComponent("Board");

let make = (~board, ~placeMarker, _children) => {
  ...component,
  render: _self =>
    <div className="board">
      (
        ReasonReact.array(
          Belt.Array.mapWithIndex(
            board, (index, a: option(GameState.player)) =>
            <div
              className="cell"
              onClick=(_event => placeMarker(index))
              key=(string_of_int(index))>
              (
                switch (a) {
                | None => ReasonReact.string("")
                | Some(player) =>
                  ReasonReact.string(
                    switch (player) {
                    | X => "X"
                    | O => "O"
                    },
                  )
                }
              )
            </div>
          ),
        )
      )
    </div>,
};