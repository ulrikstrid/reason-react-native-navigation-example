type actions =
  | Pop
  | Push Navigation.screen;

let compare a b =>
  switch (a, b) {
  | (Navigation.Home, Navigation.Home) => true
  | (Navigation.Test, Navigation.Test) => true
  | _ => false
  };

module StackNavigator =
  StackNavigator.Make {
    type navigationState = Navigation.screen;
    let compare = compare;
  };

let renderScreen pop::(pop: _ => unit) push::(push: Navigation.screen => unit) screen =>
  switch screen {
  | Navigation.Home => ReasonReact.element @@ HomeScene.make ::push ()
  | Navigation.Test => ReasonReact.element @@ TestScene.make ::pop ()
  };

let headerTitle screen =>
  switch screen {
  | Navigation.Home => "Home"
  | _ => "Test"
  };

type state = {navigationState: list Navigation.screen};

let component = ReasonReact.reducerComponent "Root";

let make _children => {
  ...component,
  initialState: fun () => {navigationState: [Home]},
  reducer: fun action state =>
    switch action {
    | Pop =>
      switch state.navigationState {
      | [] => failwith "Navigation stack is already empty"
      | [_] => ReasonReact.NoUpdate
      | [_, ...tail] => ReasonReact.Update {navigationState: tail}
      }
    | Push screen => ReasonReact.Update {navigationState: [screen, ...state.navigationState]}
    },
  render: fun {state, reduce} =>
    ReasonReact.element
    @@ StackNavigator.make
         navigationState::state.navigationState
         goBack::(reduce (fun _ => Pop))
         getHeaderConfig::headerTitle
         render::(
           renderScreen pop::(reduce (fun _ => Pop)) push::(reduce (fun screen => Push screen))
         )
};

let root = ReasonReact.wrapReasonForJs ::component (fun jsProps => make jsProps##children);
