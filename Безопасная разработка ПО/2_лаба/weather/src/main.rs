use reqwest::Client;
use scraper::{Html, Selector};
use std::error::Error;

#[derive(Debug)]
struct WeatherData {
    city: String,
    temperature: String,
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    // Город и URL для парсинга
    let city = "Новосибирск";
    let url = "https://www.gismeteo.ru/weather-novosibirsk-4690/";

    let client = Client::new();

    match fetch_weather_from_site(&client, city, url).await {
        Ok(weather) => {
            println!("=== Данные о погоде ===");
            println!("Город: {}", weather.city);
            println!("Температура: {}", weather.temperature);
        }
        Err(e) => eprintln!("Ошибка при парсинге {}: {}", city, e),
    }

    Ok(())
}

async fn fetch_weather_from_site(
    client: &Client,
    city: &str,
    url: &str,
) -> Result<WeatherData, Box<dyn Error>> {
    let response = client.get(url).send().await?;
    let body = response.text().await?;

    let document = Html::parse_document(&body);
    let temp_selector = Selector::parse(".weather-value").unwrap(); 

    // Извлекаем температуру
    let temperature = document
        .select(&temp_selector)
        .next()
        .map(|el| el.inner_html())
        .unwrap_or_else(|| "N/A".to_string());

    Ok(WeatherData {
        city: city.to_string(),
        temperature,
    })
}
