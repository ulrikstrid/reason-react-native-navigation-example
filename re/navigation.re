type screen =
  | Home
  | Test;

let compare a b =>
  switch (a, b) {
  | (Home, Home) => true
  | _ => false
  };

module Navigation =
  StackNavigator.Make {
    type navigationState = screen;
    let compare = compare;
  };
