import Vue from 'vue'
import Vuex from 'vuex'
import UserPortraits from './user-portraits'
import Popup from './popup'
import UserInfo from './user-info'
import Dialog from './dialog'
import Toast from './toast'

Vue.use(Vuex)

export default new Vuex.Store({
  modules: {
    UserPortraits,
    Popup,
    UserInfo,
    Dialog,
    Toast
  }
})