import Vue from 'vue'
import Vuex from 'vuex'
import UserPortraits from './user-portraits'
import BottomPopup from './bottom-popup'

Vue.use(Vuex)

export default new Vuex.Store({
    modules: {
        UserPortraits,
        BottomPopup
    }
})