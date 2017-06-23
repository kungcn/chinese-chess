<template>
  <div id="app">
    <router-view></router-view>
  </div>
</template>

<script>
export default {
  name: 'app'
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  width: 100%; height: 100%;
  position: absolute;
  font-size: 5vw;
}

body, html {
  position: absolute;
  top: 0; bottom: 0; left: 0; right: 0;
  margin: 0;
}
</style>
