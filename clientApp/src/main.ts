import './assets/main.css'

import { createApp } from 'vue'
import { createPinia } from 'pinia'
import LvInput from 'lightvue/input';
import LvButton from 'lightvue/button';
import LvCard from 'lightvue/card';

import App from './App.vue'
import router from './router'

const app = createApp(App)

app.component('LvInput', LvInput);
app.component('LvButton', LvButton);
app.component('LvCard', LvCard);

app.use(createPinia())
app.use(router)

app.mount('#app')
