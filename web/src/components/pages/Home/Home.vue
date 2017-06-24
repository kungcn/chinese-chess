<template>
<div>
  <mu-tabs :value="activeTab" @change="handleTabChange" class='tabs'>
    <mu-tab value="login" title="登录"/>
    <mu-tab value="register" title="注册"/>
    <mu-tab value="guest" title="游客"/>
  </mu-tabs>
  <div v-if="activeTab === 'login'">
    <form id="f_login" name="f_login" method="post" class="form">
      <mu-text-field label="username" hintText='username'/><br/>
      <mu-text-field label="password" hintText='password' type="password" labelFloat/><br/>
      <mu-raised-button @click="login()" type='submit' label="登录游戏中心" class="demo-flat-button" secondary/>
    </form>
  </div>
  <div v-if="activeTab === 'register'">
    <form id="f_register" name="f_register" method="post" class="form">
      <mu-text-field label="username" hintText='用户名不能以数字或下划线开头'/><br/>
      <mu-text-field label="password" hintText='密码长度为6-16个字符' type="password" labelFloat/><br/>
      <mu-raised-button type='submit' label="确认注册并登录" class="demo-flat-button" @click="register()" secondary/>
    </form>
  </div>
  <div v-if="activeTab === 'guest'">
    <form id="f_guest" name="f_guest" method="post" class="form">
      <mu-text-field label="username" hintText='用户名不能以数字或下划线开头'/><br/>
      <mu-raised-button type='submit' label="进入游戏大厅" class="demo-flat-button" secondary/>
    </form>
  </div>
</div>
</template>

<script>
export default {
  data () {
    return {
      activeTab: 'guest'
    }
  },
  methods: {
    handleTabChange (val) {
      this.activeTab = val
    }
  }
}
</script>

<style>
  .tabs {
    margin-bottom: 10%; 
  }
</style>