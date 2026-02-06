<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smartick SDK для Arduino - Документация</title>
    <style>
        :root {
            --primary-color: #667eea;
            --accent-color: #764ba2;
            --background-color: #ffffff;
            --card-color: #f8fafc;
            --text-primary: #1a1a1a;
            --text-secondary: #666666;
            --border-color: #e5e7eb;
            --success-color: #10b981;
            --error-color: #ef4444;
            --warning-color: #f59e0b;
            --online-color: #48bb78;
            --offline-color: #a0aec0;
            --code-bg: #1e293b;
            --code-text: #e2e8f0;
            --shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);
            --radius: 12px;
            --transition: all 0.3s ease;
        }

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif;
            line-height: 1.6;
            color: var(--text-primary);
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
        }

        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }

        /* Header Styles */
        header {
            background: var(--background-color);
            border-radius: var(--radius);
            padding: 40px;
            margin-bottom: 30px;
            box-shadow: var(--shadow);
            text-align: center;
        }

        .header-content {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 20px;
        }

        .badges {
            display: flex;
            gap: 10px;
            flex-wrap: wrap;
            justify-content: center;
        }

        .badge {
            display: inline-block;
            padding: 8px 16px;
            border-radius: 20px;
            font-size: 14px;
            font-weight: 600;
            text-decoration: none;
            transition: var(--transition);
        }

        .badge-license {
            background: var(--primary-color);
            color: white;
        }

        .badge-arduino {
            background: var(--success-color);
            color: white;
        }

        .badge-platform {
            background: var(--warning-color);
            color: white;
        }

        .badge:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 12px rgba(0, 0, 0, 0.15);
        }

        h1 {
            font-size: 3rem;
            margin-bottom: 10px;
            background: linear-gradient(135deg, var(--primary-color), var(--accent-color));
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
        }

        .subtitle {
            font-size: 1.2rem;
            color: var(--text-secondary);
            margin-bottom: 20px;
        }

        .repo-link {
            display: inline-flex;
            align-items: center;
            gap: 10px;
            background: linear-gradient(135deg, var(--primary-color), var(--accent-color));
            color: white;
            padding: 12px 24px;
            border-radius: var(--radius);
            text-decoration: none;
            font-weight: 600;
            transition: var(--transition);
        }

        .repo-link:hover {
            transform: translateY(-2px);
            box-shadow: 0 8px 16px rgba(102, 126, 234, 0.3);
        }

        /* Navigation */
        nav {
            background: var(--background-color);
            border-radius: var(--radius);
            padding: 20px;
            margin-bottom: 30px;
            box-shadow: var(--shadow);
            position: sticky;
            top: 20px;
            z-index: 100;
        }

        .toc {
            list-style: none;
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 10px;
        }

        .toc li {
            margin-bottom: 5px;
        }

        .toc a {
            display: flex;
            align-items: center;
            gap: 10px;
            color: var(--text-primary);
            text-decoration: none;
            padding: 8px 12px;
            border-radius: 8px;
            transition: var(--transition);
        }

        .toc a:hover {
            background: var(--card-color);
            color: var(--primary-color);
            transform: translateX(5px);
        }

        /* Content Sections */
        section {
            background: var(--background-color);
            border-radius: var(--radius);
            padding: 40px;
            margin-bottom: 30px;
            box-shadow: var(--shadow);
            transition: var(--transition);
        }

        section:hover {
            transform: translateY(-5px);
            box-shadow: 0 12px 24px rgba(0, 0, 0, 0.1);
        }

        h2 {
            font-size: 2rem;
            margin-bottom: 20px;
            color: var(--primary-color);
            display: flex;
            align-items: center;
            gap: 10px;
        }

        h3 {
            font-size: 1.5rem;
            margin: 25px 0 15px;
            color: var(--accent-color);
        }

        p {
            margin-bottom: 15px;
            color: var(--text-secondary);
        }

        ul, ol {
            margin-left: 20px;
            margin-bottom: 20px;
        }

        li {
            margin-bottom: 8px;
            color: var(--text-secondary);
        }

        /* Cards */
        .feature-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }

        .feature-card {
            background: var(--card-color);
            border: 1px solid var(--border-color);
            border-radius: var(--radius);
            padding: 25px;
            transition: var(--transition);
        }

        .feature-card:hover {
            border-color: var(--primary-color);
            transform: translateY(-5px);
        }

        .feature-icon {
            font-size: 2rem;
            margin-bottom: 15px;
        }

        /* Tables */
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
            border-radius: var(--radius);
            overflow: hidden;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        th {
            background: linear-gradient(135deg, var(--primary-color), var(--accent-color));
            color: white;
            padding: 15px;
            text-align: left;
        }

        td {
            padding: 15px;
            border-bottom: 1px solid var(--border-color);
        }

        tr:hover {
            background-color: var(--card-color);
        }

        /* Code Blocks */
        pre {
            background: var(--code-bg);
            color: var(--code-text);
            padding: 25px;
            border-radius: var(--radius);
            overflow-x: auto;
            margin: 20px 0;
            box-shadow: inset 0 2px 4px rgba(0, 0, 0, 0.2);
        }

        code {
            font-family: 'Courier New', Courier, monospace;
            font-size: 0.9rem;
            line-height: 1.5;
        }

        .code-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: rgba(0, 0, 0, 0.2);
            padding: 10px 20px;
            border-radius: var(--radius) var(--radius) 0 0;
            margin-top: -25px;
            margin-left: -25px;
            margin-right: -25px;
            margin-bottom: 20px;
        }

        .language {
            color: var(--code-text);
            font-weight: 600;
        }

        /* Callouts */
        .callout {
            background: linear-gradient(135deg, #667eea20, #764ba220);
            border-left: 4px solid var(--primary-color);
            padding: 20px;
            margin: 20px 0;
            border-radius: 0 var(--radius) var(--radius) 0;
        }

        .callout.warning {
            background: linear-gradient(135deg, #f59e0b20, #d9770620);
            border-left-color: var(--warning-color);
        }

        .callout.success {
            background: linear-gradient(135deg, #10b98120, #05966920);
            border-left-color: var(--success-color);
        }

        /* Quick Links */
        .quick-links {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
            gap: 15px;
            margin-top: 20px;
        }

        .quick-link {
            display: flex;
            flex-direction: column;
            align-items: center;
            text-align: center;
            padding: 20px;
            background: var(--card-color);
            border-radius: var(--radius);
            text-decoration: none;
            color: var(--text-primary);
            transition: var(--transition);
        }

        .quick-link:hover {
            background: linear-gradient(135deg, var(--primary-color), var(--accent-color));
            color: white;
            transform: translateY(-5px);
        }

        .quick-link-icon {
            font-size: 2rem;
            margin-bottom: 10px;
        }

        /* Footer */
        footer {
            background: var(--background-color);
            border-radius: var(--radius);
            padding: 40px;
            margin-top: 30px;
            box-shadow: var(--shadow);
            text-align: center;
        }

        .footer-content {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 30px;
            margin-bottom: 30px;
        }

        .footer-section h4 {
            margin-bottom: 15px;
            color: var(--primary-color);
        }

        .footer-links {
            list-style: none;
        }

        .footer-links a {
            color: var(--text-secondary);
            text-decoration: none;
            transition: var(--transition);
        }

        .footer-links a:hover {
            color: var(--primary-color);
            padding-left: 5px;
        }

        .copyright {
            padding-top: 20px;
            border-top: 1px solid var(--border-color);
            color: var(--text-secondary);
        }

        /* Responsive */
        @media (max-width: 768px) {
            .container {
                padding: 10px;
            }

            header, section, nav, footer {
                padding: 20px;
            }

            h1 {
                font-size: 2rem;
            }

            h2 {
                font-size: 1.5rem;
            }

            .toc {
                grid-template-columns: 1fr;
            }

            .feature-grid {
                grid-template-columns: 1fr;
            }
        }

        /* Animations */
        @keyframes fadeIn {
            from {
                opacity: 0;
                transform: translateY(20px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

        section {
            animation: fadeIn 0.6s ease-out;
        }

        /* Scrollbar */
        ::-webkit-scrollbar {
            width: 10px;
        }

        ::-webkit-scrollbar-track {
            background: var(--card-color);
        }

        ::-webkit-scrollbar-thumb {
            background: linear-gradient(135deg, var(--primary-color), var(--accent-color));
            border-radius: 5px;
        }

        /* Dark mode support */
        @media (prefers-color-scheme: dark) {
            :root {
                --background-color: #1a1a1a;
                --card-color: #2d2d2d;
                --text-primary: #ffffff;
                --text-secondary: #b3b3b3;
                --border-color: #404040;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <div class="header-content">
                <div class="badges">
                    <a href="#license" class="badge badge-license">MIT License</a>
                    <a href="https://www.arduino.cc/" target="_blank" class="badge badge-arduino">Arduino Compatible</a>
                    <a href="#supported-hardware" class="badge badge-platform">ESP8266/ESP32</a>
                </div>
                
                <h1>🏠 Smartick SDK for Arduino</h1>
                
                <p class="subtitle">
                    <strong>Официальная библиотека для интеграции IoT-устройств в экосистему Smartick.</strong><br>
                    Позволяет быстро создавать умные устройства (лампы, датчики, реле), которые автоматически обнаруживаются и управляются через мобильное приложение <strong>MySmartikHome</strong>.
                </p>
                
                <a href="https://github.com/oohabank/MySmartickHome-SDK" target="_blank" class="repo-link">
                    <span>📂 Репозиторий на GitHub</span>
                    <span>→</span>
                </a>
            </div>
        </header>

        <nav>
            <h2>📋 Оглавление</h2>
            <ul class="toc">
                <li><a href="#features">✨ Особенности</a></li>
                <li><a href="#supported-hardware">📦 Оборудование</a></li>
                <li><a href="#installation">⚙️ Установка</a></li>
                <li><a href="#quick-start">🚀 Быстрый старт</a></li>
                <li><a href="#examples">🧩 Примеры</a></li>
                <li><a href="#architecture">📡 Архитектура</a></li>
                <li><a href="#api">📚 API</a></li>
                <li><a href="#integration">🤝 Интеграция</a></li>
                <li><a href="#extending">🔧 Расширение</a></li>
                <li><a href="#license">📄 Лицензия</a></li>
                <li><a href="#support">🔗 Поддержка</a></li>
            </ul>
        </nav>

        <section id="features">
            <h2>✨ Особенности</h2>
            <div class="feature-grid">
                <div class="feature-card">
                    <div class="feature-icon">🛜</div>
                    <h3>Автоконфигурация Wi-Fi</h3>
                    <p>Устройство создает точку доступа для первоначальной настройки сети (Captive Portal)</p>
                </div>
                <div class="feature-card">
                    <div class="feature-icon">🔍</div>
                    <h3>Автодискавери</h3>
                    <p>Приложение автоматически обнаруживает новые устройства через MQTT</p>
                </div>
                <div class="feature-card">
                    <div class="feature-icon">📟</div>
                    <h3>Веб-интерфейс</h3>
                    <p>Встроенный веб-сервер для настройки и мониторинга</p>
                </div>
                <div class="feature-card">
                    <div class="feature-icon">💾</div>
                    <h3>Сохранение состояния</h3>
                    <p>Настройки сохраняются в EEPROM и восстанавливаются</p>
                </div>
            </div>
        </section>

        <section id="supported-hardware">
            <h2>📦 Поддерживаемое оборудование</h2>
            <table>
                <thead>
                    <tr>
                        <th>Платформа</th>
                        <th>Процессор</th>
                        <th>Рекомендуемая плата</th>
                        <th>Примечание</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><strong>ESP8266</strong></td>
                        <td>Single-core LX106, 80 МГц</td>
                        <td>NodeMCU, Wemos D1 Mini</td>
                        <td>Идеально для базовых устройств</td>
                    </tr>
                    <tr>
                        <td><strong>ESP32</strong></td>
                        <td>Dual-core LX6, до 240 МГц</td>
                        <td>ESP32 DevKit, NodeMCU-32S</td>
                        <td>Для сложных проектов (LED матрицы)</td>
                    </tr>
                </tbody>
            </table>
            <div class="callout success">
                <strong>Рекомендация:</strong> Для новых проектов выбирайте <strong>ESP32</strong> из-за большей производительности и количества GPIO.
            </div>
        </section>

        <section id="installation">
            <h2>⚙️ Установка</h2>
            
            <h3>Через Arduino IDE</h3>
            <ol>
                <li>Скачайте последний релиз <code>SmartickSDK.zip</code> со страницы <a href="https://github.com/oohabank/MySmartickHome-SDK/releases" target="_blank">Releases</a></li>
                <li>В Arduino IDE: <strong>Скетч → Подключить библиотеку → Добавить .ZIP библиотеку...</strong></li>
                <li>Выберите скачанный файл</li>
            </ol>
            
            <h3>Через PlatformIO</h3>
            <p>Добавьте зависимость в файл <code>platformio.ini</code>:</p>
            <div class="code-header">
                <span class="language">ini</span>
            </div>
            <pre><code>lib_deps = https://github.com/oohabank/MySmartickHome-SDK.git</code></pre>
            
            <h3>Зависимости</h3>
            <p>Библиотека автоматически установит:</p>
            <ul>
                <li><strong>WiFiManager</strong> для настройки Wi-Fi</li>
                <li><strong>PubSubClient</strong> для работы с MQTT</li>
                <li><strong>ArduinoJson</strong> для обработки команд</li>
                <li><strong>FastLED</strong> (опционально, для LED-устройств)</li>
            </ul>
        </section>

        <section id="quick-start">
            <h2>🚀 Быстрый старт (за 5 минут)</h2>
            
            <h3>1. Подключение оборудования</h3>
            <div class="code-header">
                <span class="language">text</span>
            </div>
            <pre><code>ESP8266/ESP32           Кнопка           Светодиод
     GPIO0 (D3) --------| |--------
     GPIO2 (D4) -------------------[LED]---||--- GND
                        GND               220 Ом</code></pre>
            
            <h3>2. Код устройства (<code>BasicSwitch.ino</code>)</h3>
            <div class="code-header">
                <span class="language">cpp</span>
            </div>
            <pre><code>#include &lt;SmartickSDK.h&gt;

// Создаем экземпляр устройства
SmartickDevice mySwitch("SmartSwitch", "BasicV1");

void handleCommand(const String& cmd, const JsonDocument& data) {
  if (cmd == "power") {
    bool state = data["value"];
    digitalWrite(2, state ? HIGH : LOW);
    Serial.println(state ? "Включено" : "Выключено");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  
  // Настройка обработчика команд
  mySwitch.setCommandHandler(handleCommand);
  
  // Запуск устройства
  mySwitch.begin();
  
  Serial.println("Устройство запущено!");
}

void loop() {
  mySwitch.loop();
  
  // Чтение кнопки для локального управления
  if (digitalRead(0) == LOW) {
    delay(50);
    bool newState = !digitalRead(2);
    digitalWrite(2, newState);
    mySwitch.sendDeviceState();
  }
}</code></pre>
            
            <h3>3. Порядок подключения</h3>
            <div class="quick-links">
                <div class="quick-link">
                    <div class="quick-link-icon">⚡</div>
                    <strong>Прошивка</strong>
                    <small>Загрузите скетч в плату</small>
                </div>
                <div class="quick-link">
                    <div class="quick-link-icon">📡</div>
                    <strong>Настройка Wi-Fi</strong>
                    <small>Подключитесь к точке доступа</small>
                </div>
                <div class="quick-link">
                    <div class="quick-link-icon">🔍</div>
                    <strong>Обнаружение</strong>
                    <small>Добавьте устройство в приложении</small>
                </div>
                <div class="quick-link">
                    <div class="quick-link-icon">🎮</div>
                    <strong>Управление</strong>
                    <small>Используйте интерфейс приложения</small>
                </div>
            </div>
        </section>

        <section id="examples">
            <h2>🧩 Примеры использования</h2>
            
            <h3>Умная RGB-лампа</h3>
            <p>Полный пример в <code>examples/SmartLamp/</code>. Включает класс <code>SmartLEDMatrix</code> с 20+ эффектами.</p>
            <ul>
                <li>Управление яркостью и цветом через приложение</li>
                <li>Циклический перебор эффектов кнопкой</li>
                <li>Автосохранение последнего состояния</li>
            </ul>
            
            <h3>Мультисенсор для умного дома</h3>
            <p>Пример в <code>examples/SensorDevice/</code> для мониторинга окружающей среды.</p>
            <ul>
                <li>Периодическая отправка телеметрии на MQTT-брокер</li>
                <li>Настраиваемый интервал измерений</li>
                <li>Пороговые значения и уведомления</li>
            </ul>
        </section>

        <section id="architecture">
            <h2>📡 Архитектура и протокол</h2>
            
            <h3>Сетевая архитектура</h3>
            <div class="code-header">
                <span class="language">text</span>
            </div>
            <pre><code>[Устройство Smartick] <----WiFi----> [Роутер] <----MQTT----> [Облачный брокер]
        |                                    |
    [Веб-интерфейс]                  [Приложение MySmartikHome]</code></pre>
            
            <h3>Протокол обмена (MQTT)</h3>
            <table>
                <thead>
                    <tr>
                        <th>Топик</th>
                        <th>Направление</th>
                        <th>Описание</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>smartick/[ID]/info</code></td>
                        <td>Устр. → Приложение</td>
                        <td>Информация об устройстве</td>
                    </tr>
                    <tr>
                        <td><code>smartick/[ID]/cmd</code></td>
                        <td>Приложение → Устр.</td>
                        <td>Команды управления</td>
                    </tr>
                    <tr>
                        <td><code>smartick/[ID]/state</code></td>
                        <td>Устр. → Приложение</td>
                        <td>Текущее состояние</td>
                    </tr>
                    <tr>
                        <td><code>smartick/discovery</code></td>
                        <td>Устр. → Приложение</td>
                        <td>Широковещательное оповещение</td>
                    </tr>
                </tbody>
            </table>
            
            <h3>Формат команды JSON</h3>
            <div class="code-header">
                <span class="language">json</span>
            </div>
            <pre><code>{
  "cmd": "команда",
  "value": "значение",
  "param1": "дополнительный_параметр"
}</code></pre>
        </section>

        <section id="api">
            <h2>📚 Справочник API</h2>
            
            <h3>Базовый класс <code>SmartickDevice</code></h3>
            
            <h4>Основные методы:</h4>
            <div class="code-header">
                <span class="language">cpp</span>
            </div>
            <pre><code>// Инициализация
void begin();
void loop();

// Управление состоянием
void setPower(bool state);
void setBrightness(uint8_t brightness); // 0-100%
void setColor(uint32_t hexColor); // 0xRRGGBB
void setSpeed(uint8_t speed); // 0-100%

// Отправка данных
void sendDeviceInfo();
void sendDeviceState();
void sendCustomData(const String& topic, const JsonDocument& data);
void sendDiscovery();</code></pre>
            
            <h4>Callback-функции:</h4>
            <div class="code-header">
                <span class="language">cpp</span>
            </div>
            <pre><code>// Вызывается при получении команды из приложения
virtual void onCommand(const String& cmd, const JsonDocument& data);

// Вызывается при успешном подключении к MQTT
virtual void onConnect();

// Вызывается при потере соединения
virtual void onDisconnect();

// Для сохранения/загрузки параметров в EEPROM
virtual void saveCustomSettings(JsonDocument& doc);
virtual void loadCustomSettings(JsonDocument& doc);</code></pre>
        </section>

        <section id="integration">
            <h2>🤝 Интеграция с приложением</h2>
            
            <h3>Стандартные команды приложения</h3>
            <table>
                <thead>
                    <tr>
                        <th>Команда</th>
                        <th>Параметры</th>
                        <th>Действие</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><code>power</code></td>
                        <td><code>"value": bool</code></td>
                        <td>Включить/выключить устройство</td>
                    </tr>
                    <tr>
                        <td><code>brightness</code></td>
                        <td><code>"value": 0-100</code></td>
                        <td>Изменить яркость</td>
                    </tr>
                    <tr>
                        <td><code>color</code></td>
                        <td><code>"r", "g", "b": 0-255</code></td>
                        <td>Изменить цвет</td>
                    </tr>
                    <tr>
                        <td><code>effect</code></td>
                        <td><code>"value": 0-N</code></td>
                        <td>Выбрать эффект (для ламп)</td>
                    </tr>
                    <tr>
                        <td><code>getInfo</code></td>
                        <td>—</td>
                        <td>Запросить информацию</td>
                    </tr>
                </tbody>
            </table>
            
            <h3>Добавление пользовательских команд</h3>
            <div class="code-header">
                <span class="language">cpp</span>
            </div>
            <pre><code>void onCommand(const String& cmd, const JsonDocument& data) override {
  SmartickDevice::onCommand(cmd, data); // Стандартная обработка
  
  if (cmd == "customMode") {
    bool enabled = data["enabled"];
    int mode = data["mode"];
    // Ваша логика здесь
  }
}</code></pre>
        </section>

        <section id="extending">
            <h2>🔧 Расширение SDK</h2>
            
            <h3>Создание специализированного класса</h3>
            <div class="code-header">
                <span class="language">cpp</span>
            </div>
            <pre><code>#include &lt;SmartickSDK.h&gt;

class MyThermostat : public SmartickDevice {
private:
    float targetTemp;
    float currentTemp;
    
public:
    MyThermostat() : SmartickDevice("SmartThermostat", "ModelT1") {}
    
    void begin() override {
        SmartickDevice::begin();
        // Инициализация датчика температуры
    }
    
    void loop() override {
        SmartickDevice::loop();
        // Логика термостата
        checkTemperature();
    }
    
protected:
    void onCommand(const String& cmd, const JsonDocument& data) override {
        if (cmd == "setTemperature") {
            targetTemp = data["value"];
            saveSettings();
        }
    }
    
    void createCustomState(JsonDocument& doc) override {
        doc["targetTemp"] = targetTemp;
        doc["currentTemp"] = currentTemp;
    }
};</code></pre>
        </section>

        <section id="license">
            <h2>📄 Лицензия</h2>
            <p>Библиотека распространяется под <strong>лицензией MIT</strong>.</p>
            <div class="code-header">
                <span class="language">text</span>
            </div>
            <pre><code>Copyright 2026 Smartick IoT

Разрешается свободное использование, копирование, изменение, объединение, публикация, 
распространение, сублицензирование и/или продажа копий Программного обеспечения.</code></pre>
        </section>

        <section id="support">
            <h2>🔗 Ссылки и поддержка</h2>
            
            <div class="quick-links">
                <a href="https://github.com/oohabank/MySmartickHome-SDK" target="_blank" class="quick-link">
                    <div class="quick-link-icon">📂</div>
                    <strong>Репозиторий SDK</strong>
                    <small>GitHub</small>
                </a>
                <a href="https://github.com/oohabank/MySmartickHome-SDK/issues" target="_blank" class="quick-link">
                    <div class="quick-link-icon">🐛</div>
                    <strong>Отчеты об ошибках</strong>
                    <small>Issues</small>
                </a>
                <a href="https://forum.smartick.io" target="_blank" class="quick-link">
                    <div class="quick-link-icon">💬</div>
                    <strong>Сообщество</strong>
                    <small>Форум</small>
                </a>
                <a href="mailto:dev-support@smartick.io" class="quick-link">
                    <div class="quick-link-icon">📧</div>
                    <strong>Техподдержка</strong>
                    <small>Email</small>
                </a>
            </div>
            
            <h3>Полезные ресурсы</h3>
            <ul>
                <li><a href="https://www.arduino.cc/reference/en/" target="_blank">Официальная документация Arduino</a></li>
                <li><a href="https://docs.espressif.com/" target="_blank">Документация по ESP8266/ESP32</a></li>
                <li><a href="https://mqtt.org/documentation/" target="_blank">Справочник по MQTT</a></li>
            </ul>
            
            <div class="callout">
                <p><strong>Smartick SDK</strong> разработан для того, чтобы превратить ваши идеи в реальные IoT-устройства за считанные часы. Создавайте, тестируйте, вдохновляйтесь! 🚀</p>
            </div>
        </section>

        <footer>
            <div class="footer-content">
                <div class="footer-section">
                    <h4>📚 Документация</h4>
                    <ul class="footer-links">
                        <li><a href="#quick-start">Быстрый старт</a></li>
                        <li><a href="#api">Справочник API</a></li>
                        <li><a href="#examples">Примеры кода</a></li>
                        <li><a href="#integration">Интеграция</a></li>
                    </ul>
                </div>
                <div class="footer-section">
                    <h4>🔧 Разработка</h4>
                    <ul class="footer-links">
                        <li><a href="#architecture">Архитектура</a></li>
                        <li><a href="#extending">Расширение SDK</a></li>
                        <li><a href="#supported-hardware">Оборудование</a></li>
                        <li><a href="#installation">Установка</a></li>
                    </ul>
                </div>
                <div class="footer-section">
                    <h4>🤝 Сообщество</h4>
                    <ul class="footer-links">
                        <li><a href="https://github.com/oohabank/MySmartickHome-SDK/issues" target="_blank">Отчеты об ошибках</a></li>
                        <li><a href="https://forum.smartick.io" target="_blank">Форум</a></li>
                        <li><a href="https://github.com/oohabank/MySmartickHome-SDK" target="_blank">GitHub</a></li>
                        <li><a href="#support">Поддержка</a></li>
                    </ul>
                </div>
            </div>
            
            <div class="copyright">
                <p>Версия документации: 1.0.0 | Актуально для SDK v1.0.0 | Последнее обновление: 6 февраля 2026 г.</p>
                <p>© 2026 Smartick IoT. Все права защищены.</p>
            </div>
        </footer>
    </div>

    <script>
        // Плавная прокрутка к якорям
        document.querySelectorAll('a[href^="#"]').forEach(anchor => {
            anchor.addEventListener('click', function (e) {
                e.preventDefault();
                const targetId = this.getAttribute('href');
                if(targetId === '#') return;
                
                const targetElement = document.querySelector(targetId);
                if(targetElement) {
                    window.scrollTo({
                        top: targetElement.offsetTop - 80,
                        behavior: 'smooth'
                    });
                }
            });
        });

        // Подсветка активного раздела
        const sections = document.querySelectorAll('section');
        const navLinks = document.querySelectorAll('nav a');
        
        window.addEventListener('scroll', () => {
            let current = '';
            sections.forEach(section => {
                const sectionTop = section.offsetTop;
                const sectionHeight = section.clientHeight;
                if(scrollY >= (sectionTop - 100)) {
                    current = section.getAttribute('id');
                }
            });

            navLinks.forEach(link => {
                link.classList.remove('active');
                if(link.getAttribute('href') === `#${current}`) {
                    link.classList.add('active');
                }
            });
        });

        // Добавляем стиль для активной ссылки
        const style = document.createElement('style');
        style.textContent = `
            .toc a.active {
                background: linear-gradient(135deg, var(--primary-color), var(--accent-color)) !important;
                color: white !important;
                transform: translateX(10px) !important;
            }
        `;
        document.head.appendChild(style);

        // Анимация при загрузке
        document.addEventListener('DOMContentLoaded', () => {
            document.body.style.opacity = '0';
            document.body.style.transition = 'opacity 0.5s ease-in';
            
            setTimeout(() => {
                document.body.style.opacity = '1';
            }, 100);
        });

        // Копирование кода
        document.querySelectorAll('pre').forEach(pre => {
            const button = document.createElement('button');
            button.className = 'copy-button';
            button.innerHTML = '📋';
            button.style.cssText = `
                position: absolute;
                top: 10px;
                right: 10px;
                background: rgba(255,255,255,0.1);
                border: none;
                color: white;
                padding: 5px 10px;
                border-radius: 5px;
                cursor: pointer;
                transition: background 0.3s;
            `;
            
            button.addEventListener('mouseover', () => {
                button.style.background = 'rgba(255,255,255,0.2)';
            });
            
            button.addEventListener('mouseout', () => {
                button.style.background = 'rgba(255,255,255,0.1)';
            });
            
            button.addEventListener('click', () => {
                const code = pre.querySelector('code').innerText;
                navigator.clipboard.writeText(code).then(() => {
                    button.innerHTML = '✅';
                    setTimeout(() => button.innerHTML = '📋', 2000);
                });
            });
            
            pre.style.position = 'relative';
            pre.appendChild(button);
        });
    </script>
</body>
</html>
