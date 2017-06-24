import Vue from 'vue'
import Router from 'vue-router'
import UserSetting from '@/components/pages/UserSetting/UserSetting'
import Home from '@/components/pages/Home/Home'
import Grade from '@/components/pages/UserSetting/Grade'

Vue.use(Router)

export default new Router({
    routes: [{
        path: '/',
        name: 'Home',
        component: Home
    }]
})