import Vue from 'vue'
import Router from 'vue-router'
import Chess from '@/components/kungcn/chess'

// using async to load components expect for the first showing one
// import UserSetting from '@/components/chenhch8/pages/UserSetting/UserSetting'
// import Grade from '@/components/chenhch8/pages/Grade/Grade'

Vue.use(Router)

export default new Router({
  routes: [{
    path: '/',
    name: 'Chess',
    component: Chess
  }, {
    path: '/setting',
    name: 'UserSetting',
    component: resolve => require(['@/components/chenhch8/pages/UserSetting/UserSetting'], resolve)
  }, {
    path: '/grade',
    name: 'Grade',
    component: resolve => require(['@/components/chenhch8/pages/Grade/Grade'], resolve)
  }, {
    path: '*',
    redirect: '/'
  }]
})
