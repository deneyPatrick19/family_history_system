import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import zhCn from 'element-plus/es/locale/lang/zh-cn'
import Cookies from 'js-cookie'
import store from './store/store'
const app = createApp(App)

app.use(router)
app.use(ElementPlus,
    {locale: zhCn,}
)
app.config.globalProperties.$cookies = Cookies;
app.use(store)
app.mount('#app')

