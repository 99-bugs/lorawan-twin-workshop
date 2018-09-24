module.exports = {
  title: 'LoRaWAN Workshop',
  description: 'Introductie tot LoRaWAN aan de hand van een STEM workshop',
  themeConfig: {
    nav: [
      {text: 'LoRaWAN', link: '/lorawan/'},
      {text: 'Sodaq Explorer', link: '/sodaq-explorer/'},
      {text: 'Sensors', link: '/sensors/'},
      {text: 'VIVES', link: 'https://www.vives.be'},
    ],
    displayAllHeaders: true,
    sidebar: 'auto',
    repo: '99-bugs/lorawan-twin-workshop'
  },
  markdown: {
    lineNumbers: true,

  },
  serviceWorker: true,
}