import Vue from 'vue'
import Router from 'vue-router'
import UserSetting from '@/components/pages/UserSetting/UserSetting'

Vue.use(Router)

export default new Router({
    routes: [{
        path: '/',
        name: 'UserSetting',
        component: UserSetting
    }]
})