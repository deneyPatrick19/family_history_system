import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import ElementPlus, { localeContextKey } from 'element-plus'
import 'element-plus/dist/index.css'
import zhCn from 'element-plus/es/locale/lang/zh-cn'
import axios from 'axios'

const app = createApp(App)

app.use(router)
app.use(ElementPlus,
    {locale: zhCn,}
)
// Vue.prototype.$axios = axios;

app.mount('#app')
