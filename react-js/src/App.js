import React, { Component } from "react";

import Board from "./Board";
import GameSummary from "./GameSummary";
import GameState from "./GameState";

class App extends Component {
  render() {
    return (
      <GameState>
        {({ state, placeMarker, resetGameState }) => (
          <div className="App">
            <header className="App-header">
              <GameSummary cells={state.cells} />
              <button onClick={resetGameState}>Reset</button>
            </header>
            <Board cells={state.cells} placeMarker={placeMarker} />
          </div>
        )}
      </GameState>
    );
  }
}

export default App;
