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
        path: '', name: 'welcome',
        component: () => import('../views/Welcome.vue')
      },
      {
        path: '/personal-history', name: 'personalhistory',
        component: () => import('../views/PersonalHistory.vue')
      },
      {
        path: '/family-tree', name: 'familytree',
        component: () => import('../views/Familytree.vue')
      },
      {
        path: '/member-list', name: 'memberlist',
        component: () => import('../views/MemberList.vue')
      },
      {
        path: '/family-table-manager', name: 'familytablemanager',
        component: () => import('../views/FamilyTableManager.vue')
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
