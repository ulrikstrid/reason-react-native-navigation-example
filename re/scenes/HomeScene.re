open ReactNative;

let component = ReasonReact.statelessComponent "Home";

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

let make push::(push: Navigation.screen => unit) _children => {
  let touchText _event => {
    Js.log "push";
    push Navigation.Test
  };
  {
    ...component,
    render: fun _self =>
      <View style=styles##container>
        <StatusBar barStyle=`lightContent hidden=true />
        <Text value="Hello from reason" />
        <Button onPress=touchText title="Push the Test screen on the stack" />
      </View>
  }
};
