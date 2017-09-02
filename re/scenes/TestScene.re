open ReactNative;

let component = ReasonReact.statelessComponent "Test";

let styles =
  StyleSheet.create
    Style.(
      {
        "container":
          style [
            flex 1.,
            justifyContent `flexStart,
            alignItems `stretch,
            backgroundColor "#EEEEEE",
            paddingTop (
              PlatformRe.os === PlatformRe.IOS ?
                20. : float_of_int StatBar.constants##currentHeight
            )
          ]
      }
    );

let make pop::(pop: Navigation.screen => unit) _children => {
  let touchText _event => {
    Js.log "pop";
    pop Navigation.Test
  };
  {
    ...component,
    render: fun _self =>
      <View style=styles##container>
        <StatusBar barStyle=`lightContent hidden=true />
        <Text value="Hello from test page" />
        <Button onPress=touchText title="Pop this screen from the stack" />
      </View>
  }
};
