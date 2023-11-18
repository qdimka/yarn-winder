import { ref, computed } from 'vue'
import { defineStore } from 'pinia'

export const useCounterStore = defineStore('counter', () => {
  const count = ref(0)
  const started = ref(false)

  function start() {
    started.value = true;
  }

  function stop() {
    started.value = false;
  }

  function updateVal(value: number) {
    count.value = value
  }

  function updateStarted(value: boolean) {
    started.value = value
  }

  return { count, started, updateVal,updateStarted, start, stop }
})
