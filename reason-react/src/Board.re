open ReasonReact;

let component = statelessComponent("Board");

let make = (~state: GameState.state, ~placeMarker, _children) => {
  ...component,
  render: _self =>
    <div className="board">
      (
        array(
          Array.mapi(
            (index, marker: GameState.marker) =>
              <div
                key=(string_of_int(index))
                className="cell"
                onClick=(_evt => placeMarker(index))>
                (string(GameState.stringOfMarker(marker)))
              </div>,
            state.cells,
          ),
        )
      )
    </div>,
};