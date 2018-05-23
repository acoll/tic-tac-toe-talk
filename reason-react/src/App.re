open ReasonReact;

let component = statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <GameState
      render=(
        ({state, gameState, resetState, placeMarker}) => {
          Js.log(state);
          <div className="App">
            <header className="App-header">
              <GameSummary gameState />
              <button onClick=(_event => resetState())>
                (string("Reset"))
              </button>
            </header>
            <Board state placeMarker />
          </div>;
        }
      )
    />,
};