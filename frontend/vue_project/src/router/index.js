import { createRouter, createWebHistory } from 'vue-router'


const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/', redirect: '/login'
    },
    {
      path: '/login', name: 'login', 
      component: () => import('../views/Login.vue')
    },
    {
      path: '/home', name: 'home', 
      component: () => import('../views/Home.vue'),
      children:[
      {
        path: '/member-history', name: 'memberhistory',
        component: () => import('../views/MemberHistory.vue')
      },
      {
        path: '/add-member', name: 'addmember',
        component: () => import('../views/AddMember.vue')
      },
      {
        path: '/family-tree', name: 'familytree',
        component: () => import('../views/Familytree.vue')
      },
    ]
    },
    {
      path: '/signup', name: 'sign',
      component: () => import('../views/Sign.vue')
    }
  ]
})

export default router
